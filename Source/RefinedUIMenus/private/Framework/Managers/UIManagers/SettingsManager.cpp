// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "MainMenuManager.h"
#include "Components/WidgetSwitcher.h"
#include "Framework/Managers/SavingManager/SettingsSaveManager.h"
#include "Framework/UIWidgets/SettingsWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

//these set the variables to the loaded version
void USettingsManager::SetMasterVolume(float Value)
{
	MasterVolumeChanged(Value);
}

void USettingsManager::SetMusicVolume(float Value)
{
	MusicVolumeChanged(Value);
}

void USettingsManager::SetSfxVolume(float Value)
{
	SFXVolumeChanged(Value);
}

void USettingsManager::SetFullscreen(bool Enabled)
{
	bIsFullscreen = Enabled;
}

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

void USettingsManager::SetSettingsSaveManager(USettingsSaveManager* InSettingsSaveManager)
{
	SaveManager = InSettingsSaveManager;
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
	SetState(ESettingsMenuStates::General);
}

void USettingsManager::OpenGraphics()
{
	SetState(ESettingsMenuStates::Graphics);
}

void USettingsManager::OpenAudio()
{
	SetState(ESettingsMenuStates::Audio);
}

void USettingsManager::OpenControls()
{
	SetState(ESettingsMenuStates::Controls);
}

void USettingsManager::GoBack()
{
	if (!MainMenuManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("No main menu ref"));
		return;
	}
	MainMenuManager->OpenMainMenu();
}

void USettingsManager::ApplySettings()
{
	UE_LOG(LogTemp, Log, TEXT("Apply settings has NOT reached the save settings"));
	if (SaveManager)
	{
		UE_LOG(LogTemp, Log, TEXT("Apply settings has reached the save settings"));

		SaveManager->SaveSettings();
	}
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
}

void USettingsManager::MusicVolumeChanged(float Volume)
{
	MusicVolume = Volume;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Music Volume: No Player Controller")); return;
	} 
	if (!SettingsSoundMix)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Music Volume: No Sound Mix")); return;
	} 
	if (!MusicSoundClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Music Volume: No Music Sound Class")); return;
	} 
	
	UGameplayStatics::SetSoundMixClassOverride( PlayerController, SettingsSoundMix, MusicSoundClass, MusicVolume, 1.0f, 0.0f, false ); 
}

void USettingsManager::ChangefullScreen(bool IsInFullscreen)
{
	SetFullscreen(IsInFullscreen);
	
	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
	
	bIsFullscreen = IsInFullscreen;
	
	if (bIsFullscreen)
	{
		GameSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	}
	else
	{
		GameSettings->SetFullscreenMode(EWindowMode::Windowed);
	}
	
	GameSettings->ApplyResolutionSettings(false);
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

