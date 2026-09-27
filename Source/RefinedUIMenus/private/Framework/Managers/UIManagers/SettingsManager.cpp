// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "MainMenuManager.h"
#include "Components/WidgetSwitcher.h"
#include "Framework/Managers/SavingManager/SettingsSaveManager.h"
#include "Framework/UIWidgets/SettingsWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

#pragma region Getters/Setters 
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

void USettingsManager::SetResolution(int32 Width, int32 Height)
{
	ResolutionWidth = Width;
	ResolutionHeight = Height;
	
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	
	if (!GameUserSettings)
	{
		return;
	}
	GameUserSettings->SetScreenResolution(FIntPoint(Width,Height));
	GameUserSettings->ApplySettings(false);
}

int32 USettingsManager::GetResolutionWidth() const
{
	return ResolutionWidth;
}

int32 USettingsManager::GetResolutionHeight() const
{
	return ResolutionHeight;
}

EWindowMode::Type USettingsManager::GetWindowMode() const
{
	return WindowMode;
}

void USettingsManager::SetWindowMode(EWindowMode::Type NewWindowMode)
{
	 WindowMode = NewWindowMode;
	
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	if (!GameUserSettings)
	{
		return;
	}
	GameUserSettings->SetFullscreenMode(NewWindowMode);
	GameUserSettings->ApplySettings(false);
}

bool USettingsManager::GetVSyncEnabled() const
{
	return bVSyncEnabled;
}

void USettingsManager::SetVSyncEnabled(bool Enabled)
{
	bVSyncEnabled = Enabled;
	
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	
	if (!GameUserSettings)
	{
		return;
	}
	GameUserSettings->SetVSyncEnabled(Enabled);
	GameUserSettings->ApplySettings(false);
}

float USettingsManager::GetFrameRateLimit() const
{
	return FrameRateLimit;
}

void USettingsManager::SetFrameRateLimit(float Value)
{
	FrameRateLimit = Value;
	
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	
	if (!GameUserSettings)
	{
		return;
	}
	
	GameUserSettings->SetFrameRateLimit(Value);
	GameUserSettings->ApplySettings(false);
}

void USettingsManager::SetMainMenuManager(UMainMenuManager* InMainMenuManager)
{
	MainMenuManager = InMainMenuManager;
}

void USettingsManager::SetSettingsSaveManager(USettingsSaveManager* InSettingsSaveManager)
{
	SaveManager = InSettingsSaveManager;
}
#pragma endregion

#pragma region Init Setup
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
	
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	
	if (GameUserSettings)
	{
		ResolutionWidth = GameUserSettings->GetScreenResolution().X;
		ResolutionHeight = GameUserSettings->GetScreenResolution().Y;
		
		WindowMode = GameUserSettings->GetFullscreenMode();
		
		bVSyncEnabled = GameUserSettings->IsVSyncEnabled();
		
		FrameRateLimit = GameUserSettings->GetFrameRateLimit();
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
#pragma endregion

#pragma region Button Click handling
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
	UE_LOG(LogTemp,Log,TEXT("Settings Manager ApplySettings called"));

	if (!SaveManager)
	{
		UE_LOG(LogTemp,Warning,TEXT("Cannot save settings: SaveManager is null")
		);

		return;
	}

	SaveManager->SaveSettings();
	
	CaptureSavedSettings();

	UE_LOG(LogTemp,Log,TEXT("Settings successfully saved"));
}
#pragma endregion

#pragma region Audio Management
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
	
	MarkSettingsChanged();
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
	
	MarkSettingsChanged();
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
	
	MarkSettingsChanged();
}
#pragma endregion

#pragma region Graphics Management

void USettingsManager::ChangeWindowMode(const FString& NewWindowModeString)
{
	EWindowMode::Type NewWindowMode;

	if (NewWindowModeString == TEXT("Windowed"))
	{
		NewWindowMode = EWindowMode::Windowed;
	}
	else if (NewWindowModeString == TEXT("Borderless"))
	{
		NewWindowMode = EWindowMode::WindowedFullscreen;
	}
	else if (NewWindowModeString == TEXT("Fullscreen"))
	{
		NewWindowMode = EWindowMode::Fullscreen;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Invalid window mode selected: %s"),*NewWindowModeString);

		return;
	}

	SetWindowMode(NewWindowMode);

	MarkSettingsChanged();

	UE_LOG(LogTemp,Log,TEXT("Window mode changed to %s"),*NewWindowModeString);
}

void USettingsManager::ChangeResolution(const FString& NewResolution)
{
	int32 Width = 0;
	int32 Height = 0;

	if (NewResolution == TEXT("1280 x 720"))
	{
		Width = 1280;
		Height = 720;
	}
	else if (NewResolution == TEXT("1600 x 900"))
	{
		Width = 1600;
		Height = 900;
	}
	else if (NewResolution == TEXT("1920 x 1080"))
	{
		Width = 1920;
		Height = 1080;
	}
	else if (NewResolution == TEXT("2560 x 1440"))
	{
		Width = 2560;
		Height = 1440;
	}
	else if (NewResolution == TEXT("3840 x 2160"))
	{
		Width = 3840;
		Height = 2160;
	}

	if (Width <= 0 || Height <= 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Invalid resolution selected: %s"),*NewResolution);

		return;
	}

	SetResolution(Width, Height);

	MarkSettingsChanged();

	UE_LOG(LogTemp,Log,TEXT("Resolution changed to %d x %d"),Width,Height);
}

void USettingsManager::ChangeFrameRateLimit(const FString& NewFrameRateLimit)
{
	float NewFrameRate = 60.0f;

	if (NewFrameRateLimit == TEXT("30 FPS"))
	{
		NewFrameRate = 30.0f;
	}
	else if (NewFrameRateLimit == TEXT("60 FPS"))
	{
		NewFrameRate = 60.0f;
	}
	else if (NewFrameRateLimit == TEXT("120 FPS"))
	{
		NewFrameRate = 120.0f;
	}
	else if (NewFrameRateLimit == TEXT("144 FPS"))
	{
		NewFrameRate = 144.0f;
	}
	else if (NewFrameRateLimit == TEXT("165 FPS"))
	{
		NewFrameRate = 165.0f;
	}
	else if (NewFrameRateLimit == TEXT("240 FPS"))
	{
		NewFrameRate = 240.0f;
	}
	else if (NewFrameRateLimit == TEXT("Unlimited"))
	{
		NewFrameRate = 0.0f;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Invalid frame rate selected: %s"),*NewFrameRateLimit);

		return;
	}

	SetFrameRateLimit(NewFrameRate);

	MarkSettingsChanged();

	UE_LOG(LogTemp,Log,TEXT("Frame rate changed to %s"),*NewFrameRateLimit);
}

void USettingsManager::ChangeVsync(bool bEnabled)
{
	SetVSyncEnabled(bEnabled);

	MarkSettingsChanged();

	UE_LOG(LogTemp,Log,TEXT("VSync changed to %s"),bEnabled ? TEXT("Enabled") : TEXT("Disabled"));
}
#pragma endregion

#pragma region Resetting to default/ unsaved changes 
void USettingsManager::MarkSettingsChanged()
{
	bHasUnsavedChanges = true;
	UE_LOG(LogTemp, Warning, TEXT("settings have been marked as saved"));
}

bool USettingsManager::HasUnsavedChanges() const
{
	return bHasUnsavedChanges;
}

void USettingsManager::ClearUnsavedChanges()
{
	bHasUnsavedChanges = false;
	UE_LOG(LogTemp, Warning, TEXT("cleared out changes"));
}

void USettingsManager::RestoreSavedSettings()
{
	UE_LOG(LogTemp,Warning,TEXT("Restoring previously saved settings"));

	SetMasterVolume(SavedMasterVolume);
	SetMusicVolume(SavedMusicVolume);
	SetSfxVolume(SavedSFXVolume);

	SetResolution(SavedResolutionWidth,SavedResolutionHeight);

	SetWindowMode(SavedWindowMode);

	SetVSyncEnabled(SavedVsyncEnabled);

	SetFrameRateLimit(SavedFrameRateLimit);

	ClearUnsavedChanges();

	UE_LOG(LogTemp,Warning,TEXT("Previously saved settings restored"));
}

void USettingsManager::ResetToDefaults()
{
	UE_LOG(LogTemp,Warning,TEXT("Resetting settings to defaults"));

	SetMasterVolume(1.0f);
	SetMusicVolume(1.0f);
	SetSfxVolume(1.0f);

	SetResolution(1920, 1080);

	SetWindowMode(EWindowMode::Windowed);

	SetVSyncEnabled(false);

	SetFrameRateLimit(60.0f);

	MarkSettingsChanged();

	UE_LOG(LogTemp,Warning,TEXT("Settings reset to defaults - changes NOT saved"));
}

void USettingsManager::CaptureSavedSettings()
{
	SavedMasterVolume = MasterVolume;
	SavedMusicVolume = MusicVolume;
	SavedSFXVolume = SFXVolume;
	
	SavedResolutionWidth = ResolutionWidth;
	SavedResolutionHeight = ResolutionHeight;
	
	SavedWindowMode = WindowMode;
	
	SavedVsyncEnabled = bVSyncEnabled;
	
	SavedFrameRateLimit = FrameRateLimit;
	
	bHasUnsavedChanges = false;
	UE_LOG(LogTemp, Warning, TEXT("Settings have been captured"));
}
#pragma endregion

#pragma region State Management
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
#pragma endregion

