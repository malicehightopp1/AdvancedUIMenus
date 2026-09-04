// Fill out your copyright notice in the Description page of Project Settings.
#include "Framework/Managers/UIManagers/MainMenuManager.h"

#include "SettingsManager.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Services/ServiceLocatorSubSystem.h"
#include "Framework/UIWidgets/MainMenuWidget.h"
#include "Framework/UIWidgets/SettingsWidget.h"

void UMainMenuManager::Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass, TSubclassOf<USettingsWidget> InSettingsWidgetClass)
{
	PlayerController = InPlayerController;
	MainMenuWidgetClass = InMainMenuWidgetClass;
	SettingsWidgetClass = InSettingsWidgetClass;
	
	CreateWidgets();
	if (ValidateWidgets() != true)
	{
		return;
	}
	
	CurrentState = EMainMenuState::Main;
	StateStack.Empty();
	
	//Does both input handling and state handling, also sets ui active based on state
	ApplyState();
}

bool UMainMenuManager::ValidateWidgets() const
{
	if (!PlayerController)
	{
		return false;
	}
	if (!MainMenuWidget)
	{
		return false;
	}
	if (!SettingsWidget)
	{
		return false;
	}
	return true;
}

void UMainMenuManager::StartGame()
{
	UE_LOG(LogTemp,Log,TEXT("Start Clicked"));
	SetState(EMainMenuState::Playing);
}

void UMainMenuManager::OpenSettings()
{
	UE_LOG(LogTemp,Log,TEXT("Settings Clicked"));
	SetState(EMainMenuState::Settings);
}

void UMainMenuManager::QuitGame()
{
	UE_LOG(LogTemp,Log,TEXT("Quit Clicked"));
	
	//closes the game cleanly allowing things to turn off and close
	FGenericPlatformMisc::RequestExit(false);
}

void UMainMenuManager::GoBack()
{
	if (StateStack.IsEmpty())
	{
		return;
	}
	
	CurrentState = StateStack.Last();
	
	StateStack.Pop();
	
	ApplyState();
}

void UMainMenuManager::CreateWidgets()
{
	if (!PlayerController){return;}

	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogTemp,Error,TEXT("MainMenuWidgetClass is NOT assigned!"));

		return;
	}
	if (!SettingsWidgetClass)
	{
		UE_LOG(LogTemp,Error,TEXT("SettingsWidgetClass is NOT assigned!"));

		return;
	}

	//Main Menu widgets
	MainMenuWidget = CreateWidget<UMainMenuWidget>(PlayerController,MainMenuWidgetClass);

	if (!MainMenuWidget)
	{
		UE_LOG(LogTemp,Error,TEXT("Failed to create MainMenuWidget!"));

		return;
	}
	MainMenuWidget->SetMainMenuManager(this); //setting reference after creation

	MainMenuWidget->AddToViewport(0);

	UE_LOG(LogTemp, Warning,TEXT("Main Menu Widget created and added to viewport"));

	//Settings widget
	SettingsWidget = CreateWidget<USettingsWidget>(PlayerController, SettingsWidgetClass);
	
	if (!SettingsWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create SettingsWidget"));
		
		return;
	}
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(PlayerController);
	
	if (!Services)
	{
		return;
	}
	USettingsManager* SettingsManagerRef = Services->GetSettingsManager();
	
	if (!SettingsManagerRef)
	{
		return;
	}
	
	SettingsWidget->SetSettingsManager(SettingsManagerRef);
	SettingsWidget->AddToViewport(1);
	SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuManager::SetState(EMainMenuState NewState)
{
	if (bIsTransitioning)
	{
		return;
	}
	if(CurrentState == NewState)
	{
		return;
	}
	
	//"saving" the previous state
	StateStack.Add(CurrentState);
	
	CurrentState = NewState;
	
	ApplyState();
}

void UMainMenuManager::ApplyState()
{
	if (!MainMenuWidget || !SettingsWidget)
	{
		return;
	}
	
	switch (CurrentState)
	{
	case EMainMenuState::Main:
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EMainMenuState::Settings:
		MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EMainMenuState::Playing:
		MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		break;
		
	default:
		break;
	}
	UpdateInputMode();
}

EMainMenuState UMainMenuManager::GetCurrentState() const
{
	return CurrentState;
}

void UMainMenuManager::UpdateInputMode()
{
	if (!PlayerController)
	{
		return;
	}
	if (CurrentState == EMainMenuState::Main || CurrentState == EMainMenuState::Settings || CurrentState == EMainMenuState::Credits)
	{
		SetupUIInputMode();
	}
	else //if in play mode 
	{
		SetupGameInputMode();
	}
}

void UMainMenuManager::SetupUIInputMode()
{
	UE_LOG(LogTemp,Warning,TEXT("Input mode set to ui"));
	FInputModeGameAndUI InputMode;
	
	if (CurrentState == EMainMenuState::Settings && SettingsWidget)
	{
		InputMode.SetWidgetToFocus(SettingsWidget->TakeWidget());
	}
	else if (MainMenuWidget)
	{
		InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
	}

	InputMode.SetHideCursorDuringCapture(false);
	
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenuManager::SetupGameInputMode()
{
	UE_LOG(LogTemp,Warning,TEXT("Input mode set to Game"));

	FInputModeGameOnly InputMode;
	
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}
