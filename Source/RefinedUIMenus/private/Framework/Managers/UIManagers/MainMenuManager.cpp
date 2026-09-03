// Fill out your copyright notice in the Description page of Project Settings.
#include "Framework/Managers/UIManagers/MainMenuManager.h"

#include "Blueprint/UserWidget.h"
#include "Framework/UIWidgets/MainMenuWidget.h"
#include "Framework/UIWidgets/SettingsWidget.h"

void UMainMenuManager::Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass, TSubclassOf<USettingsWidget> InSettingsWidgetClass)
{
	PlayerController = InPlayerController;
	MainMenuWidgetClass = InMainMenuWidgetClass;
	SettingsWidgetClass = InSettingsWidgetClass;
	
	UE_LOG(LogTemp, Warning, TEXT("UI Manager was inited"));
	
	CreateWidgets();
	//BindWidgetEvents();
	
	CurrentState = EMainMenuState::Main;
	TargetState = EMainMenuState::Main;
	
	UpdateInputMode();
}

void UMainMenuManager::StartGame()
{
	UE_LOG(LogTemp,Log,TEXT("Start Clicked"));
	SetState(EMainMenuState::Playing);
	
	UpdateInputMode();
}

void UMainMenuManager::OpenSettings()
{
	UE_LOG(LogTemp,Log,TEXT("Settings Clicked"));
	SetState(EMainMenuState::Settings);
	SettingsWidget->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuManager::QuitGame()
{
	UE_LOG(LogTemp,Log,TEXT("Quit Clicked"));
	
	//closes the game cleanly allowing things to turn off and close
	FGenericPlatformMisc::RequestExit(false);
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
	
	MainMenuWidget->SetMainMenuManager(this); //setting reference after creation
	if (!MainMenuWidget)
	{
		UE_LOG(LogTemp,Error,TEXT("Failed to create MainMenuWidget!"));

		return;
	}

	MainMenuWidget->AddToViewport(0);

	UE_LOG(LogTemp, Warning,TEXT("Main Menu Widget created and added to viewport"));

	//Settings widget
	SettingsWidget = CreateWidget<USettingsWidget>(PlayerController, SettingsWidgetClass);
	if (!SettingsWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create SettingsWidget"));
		
		return;
	}
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
	
	CurrentState = NewState;
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
	if (CurrentState == EMainMenuState::Playing)
	{
		SetupGameInputMode();
		UE_LOG(LogTemp,Warning,TEXT("this is set to playing"));
	}
	else
	{
		SetupUIInputMode();
	}
}

void UMainMenuManager::SetupUIInputMode()
{
	UE_LOG(LogTemp,Warning,TEXT("Input mode set to ui"));
	FInputModeGameAndUI InputMode;
	
	if (MainMenuWidget)
	{
		InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
	}
	else
	{
		InputMode.SetWidgetToFocus(nullptr);
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
