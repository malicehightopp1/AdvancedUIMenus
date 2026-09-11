// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "MainMenuManager.h"
#include "Components/WidgetSwitcher.h"
#include "Framework/UIWidgets/SettingsWidget.h"
#include "Kismet/GameplayStatics.h"

void USettingsManager::Initialize(APlayerController* InPlayerController, TSubclassOf<USettingsWidget> InSettingsWidget,USoundClass* InMasterSoundClass, USoundClass* InMusicSoundClass, USoundClass* InSFXSoundClass,USoundMix* InSettingsSoundMix)
{
	PlayerController = InPlayerController;
	SettingsWidgetClass = InSettingsWidget;

	MasterSoundClass = InMasterSoundClass;
	MusicSoundClass = InMusicSoundClass;
	SFXSoundClass = InSFXSoundClass;
	SettingsSoundMix = InSettingsSoundMix;

	CurrentState = ESettingsMenuStates::General;
	StateStack.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Settings Manager Initialized"));
	
	if (PlayerController && SettingsSoundMix)
	{
		UGameplayStatics::PushSoundMixModifier(PlayerController,SettingsSoundMix);

		UE_LOG(LogTemp, Warning, TEXT("Settings Sound Mix Activated"));
	}
}

void USettingsManager::SetSettingsWidget(USettingsWidget* InSettingsWidget)
{
	SettingsWidget = InSettingsWidget;
	if (!SettingsWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Settings Widget in SettingsManager its null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Settings Widget"));
	ApplyState();
}

void USettingsManager::SetMainMenuManager(UMainMenuManager* InMainMenuManager)
{
	MainMenuManager = InMainMenuManager;
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
	UE_LOG(LogTemp, Warning, TEXT("Exitting Settings"));
	
	if (!MainMenuManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("No main menu ref"));
		return;
	}
	MainMenuManager->OpenMainMenu();
}

void USettingsManager::MasterVolumeChanged(float Volume)
{
	MasterVolume = Volume;

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Master Volume: No Player Controller"));
		return;
	}

	if (!SettingsSoundMix)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Master Volume: No Sound Mix"));
		return;
	}

	if (!MasterSoundClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Master Volume: No Master Sound Class"));
		return;
	}

	UGameplayStatics::SetSoundMixClassOverride(PlayerController,SettingsSoundMix,MasterSoundClass,MasterVolume,1.0f,0.0f,true);

	UE_LOG(LogTemp,Warning,TEXT("Master Volume Changed: %f"),MasterVolume);
}

void USettingsManager::SFXVolumeChanged(float Volume)
{
	SFXVolume = Volume;

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change SFX Volume: No Player Controller"));
		return;
	}

	if (!SettingsSoundMix)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change SFX Volume: No Sound Mix"));
		return;
	}

	if (!SFXSoundClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change SFX Volume: No SFX Sound Class"));
		return;
	}

	UGameplayStatics::SetSoundMixClassOverride(PlayerController,SettingsSoundMix,SFXSoundClass,SFXVolume,1.0f,0.0f,false);

	UE_LOG(LogTemp,Warning,TEXT("SFX Volume Changed: %f"),SFXVolume);
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
	StateStack.Add(CurrentState);
	
	CurrentState = NewState;
	
	ApplyState();
}

void USettingsManager::ApplyState()
{
	if (!SettingsWidget)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Applying Settings"));
	switch (CurrentState)
	{
		case ESettingsMenuStates::General:
			SettingsWidget->PanelSwitcher->SetActiveWidgetIndex(0);
		break;
		case ESettingsMenuStates::Graphics:
			SettingsWidget->PanelSwitcher->SetActiveWidgetIndex(1);
		break;
		case ESettingsMenuStates::Audio:
			SettingsWidget->PanelSwitcher->SetActiveWidgetIndex(2);
		break;
		case ESettingsMenuStates::Controls:
			SettingsWidget->PanelSwitcher->SetActiveWidgetIndex(3);
		break;
		
		default:
			break;
	}
}

