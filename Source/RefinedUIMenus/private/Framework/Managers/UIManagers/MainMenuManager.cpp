// Fill out your copyright notice in the Description page of Project Settings.
#include "Framework/Managers/UIManagers/MainMenuManager.h"

#include "SettingsManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Widget.h"
#include "Framework/Managers/Player/PlayerCamera/MainMenuCamera.h"
#include "Framework/Services/ServiceLocatorSubSystem.h"
#include "Framework/UIWidgets/MainMenuWidget.h"
#include "Input/Reply.h"
#include "Framework/UIWidgets/SettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

class USoundBase;

#pragma region Initial Setup functions

void UMainMenuManager::Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass, TSubclassOf<USettingsWidget> InSettingsWidgetClass, AMainMenuCamera* InMainMenuCamera,USoundBase* InMainMenuMusic)
{
	PlayerController = InPlayerController;
	MainMenuWidgetClass = InMainMenuWidgetClass;
	SettingsWidgetClass = InSettingsWidgetClass;
	MainMenuMusic = InMainMenuMusic;
	
	MainMenuCamera = InMainMenuCamera;
	if (MainMenuCamera)
	{
		MainMenuCamera->OnCameraTransitionFinished.AddDynamic(this, &UMainMenuManager::OnCameraTransitionFinished);
	}
	CreateWidgets();
	if (ValidateWidgets() != true)
	{
		return;
	}
	if (MainMenuMusic)
	{
		UGameplayStatics::PlaySound2D(this, MainMenuMusic);
		UE_LOG(LogTemp,Log,TEXT("Sound worked"));
	}
	
	PlayerController->SetViewTarget(MainMenuCamera);

	CurrentState = EMainMenuState::Idle;
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
	MainMenuWidget->SetIsFocusable(true);
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
	
	SettingsManagerRef->SetMainMenuManager(this);
	SettingsManagerRef->SetSettingsWidget(SettingsWidget);
	
	SettingsWidget->SetSettingsManager(SettingsManagerRef);
	
	SettingsWidget->AddToViewport(1);
	SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Widget Button Functions 

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

void UMainMenuManager::OpenCredits()
{
	UE_LOG(LogTemp,Log,TEXT("Credits Clicked"));
	SetState(EMainMenuState::Credits);
}

void UMainMenuManager::QuitGame()
{
	UE_LOG(LogTemp,Log,TEXT("Quit Clicked"));
	
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}

void UMainMenuManager::GoBack()
{
	if (bIsTransitioning)
	{
		return;
	}
	if (StateStack.IsEmpty())
	{
		return;
	}
	EMainMenuState PreviousState = StateStack.Last();
	
	StateStack.Pop();

	CurrentState = PreviousState;
	
	bIsTransitioning = true;

	TransitionCamera(CurrentState);
}

void UMainMenuManager::OpenMainMenu()
{
	UE_LOG(LogTemp,Log,TEXT("Should go straight back to main menu"));
	
	StateStack.Empty();
	
	SetState(EMainMenuState::Main);
}

void UMainMenuManager::PressAnyKey()
{
	if (CurrentState != EMainMenuState::Idle)
	{
		return;
	}
	SetState(EMainMenuState::Main);
}
#pragma endregion

#pragma region Transition Managing
void UMainMenuManager::TransitionCamera(EMainMenuState NewState)
{
	if (!MainMenuCamera)
	{
		bIsTransitioning = false;
		ApplyState();
		return;
	}


	switch (NewState)
	{
	case EMainMenuState::Idle:
		
		MainMenuCamera->MoveToTransform(
			MainMenuCamera->IdleLocation,
			MainMenuCamera->IdleRotation
		);

		break;

	case EMainMenuState::Main:

		MainMenuCamera->MoveToTransform(
			MainMenuCamera->MainMenuLocation,
			MainMenuCamera->MainMenuRotation
		);

		break;

	case EMainMenuState::Settings:

		MainMenuCamera->MoveToTransform(
			MainMenuCamera->SettingsLocation,
			MainMenuCamera->SettingsRotation
		);

		break;

	case EMainMenuState::Credits:

		MainMenuCamera->MoveToTransform(
			MainMenuCamera->CreditsLocation,
			MainMenuCamera->CreditsRotation
		);

		break;

	default:
		
		bIsTransitioning = false;
		ApplyState();
		
		break;
	}
}

void UMainMenuManager::OnCameraTransitionFinished()
{
	bIsTransitioning = false;
	
	ApplyState();
}
#pragma endregion

#pragma region State Management
void UMainMenuManager::SetState(EMainMenuState NewState)
{
	if(CurrentState == NewState)
	{
		return;
	}
	if (bIsTransitioning)
	{
		return;
	}

	//"saving" the previous state
	StateStack.Add(CurrentState);
	
	CurrentState = NewState;
	
	bIsTransitioning = true;
	
	TransitionCamera(NewState);
}

void UMainMenuManager::ApplyState()
{
	if (!MainMenuWidget || !SettingsWidget)
	{
		return;
	}
	
	switch (CurrentState)
	{
	case 
		EMainMenuState::Idle:
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidget->PanelSwitcher->SetActiveWidgetIndex(0);
		break;
	case EMainMenuState::Main:
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidget->PanelSwitcher->SetActiveWidgetIndex(1);
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
#pragma endregion

#pragma region Input Management
void UMainMenuManager::UpdateInputMode()
{
	if (!PlayerController)
	{
		return;
	}
	if (CurrentState == EMainMenuState::Main || CurrentState == EMainMenuState::Settings || CurrentState == EMainMenuState::Credits || CurrentState == EMainMenuState::Idle)
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
	if (!PlayerController)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Input mode set to UI"));

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
	
	if (CurrentState == EMainMenuState::Idle || CurrentState == EMainMenuState::Main)
	{
		UE_LOG(LogTemp,Warning,TEXT("Input mode set to Idle"));
		MainMenuWidget->SetKeyboardFocus();
	}
}

void UMainMenuManager::SetupGameInputMode()
{
	UE_LOG(LogTemp,Warning,TEXT("Input mode set to Game"));

	FInputModeGameOnly InputMode;
	
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}
#pragma endregion
