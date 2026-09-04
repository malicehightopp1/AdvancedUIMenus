// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "Framework/UIWidgets/SettingsWidget.h"

void USettingsManager::Initialize(APlayerController* InPlayerController, TSubclassOf<USettingsWidget> InSettingsWidget)
{
	PlayerController = InPlayerController;
	SettingsWidgetClass = InSettingsWidget;
	
	CurrentState = ESettingsMenuStates::General;
	StateStack.Empty();
	
	if (!Validate())
	{
		return;
	}
	ApplyState();		
}

bool USettingsManager::Validate() const
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Controller"));
		return false;
	}
	if (!SettingsWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Settings Widget in SettingsManager"));
		return false;
	}
	return true;
}

void USettingsManager::OpenGeneral()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening General"));
	SetState(ESettingsMenuStates::General);
}

void USettingsManager::OpenGraphics()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening Graphics"));
	SetState(ESettingsMenuStates::Graphics);
}

void USettingsManager::OpenAudio()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening Audio"));
	SetState(ESettingsMenuStates::Audio);
}

void USettingsManager::OpenControls()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening Controls"));
	SetState(ESettingsMenuStates::Controls);
}

void USettingsManager::GoBack()
{
	if (!StateStack.IsEmpty())
	{
		CurrentState = StateStack.Last();
		
		StateStack.Pop();
		
		ApplyState();
		
		return;
	}
	ExittingSettings();
}

void USettingsManager::ExittingSettings()
{
	UE_LOG(LogTemp, Warning, TEXT("Exitting Settings"));
}

ESettingsMenuStates USettingsManager::GetCurrentState() const
{
	return CurrentState;
}

void USettingsManager::SetState(ESettingsMenuStates NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}
	StateStack.Add(NewState);
	
	CurrentState = NewState;
	
	ApplyState();
}

void USettingsManager::ApplyState()
{
	if (!SettingsWidget)
	{
		return;
	}
}

