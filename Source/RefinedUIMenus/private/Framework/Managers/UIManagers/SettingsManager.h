// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SettingsManager.generated.h"

class UConfirmQuit;
class USettingsWidget;
class UMainMenuManager;
class USoundClass;
class USoundMix;
class USettingsSaveManager;

UENUM(BlueprintType)
enum class ESettingsMenuStates : uint8
{
	General,
	Graphics,
	Audio,
	Controls
};

UCLASS()
class USettingsManager : public UObject
{
	GENERATED_BODY()

public:
	// =========================================================
	// Getters
	// =========================================================
	float GetMasterVolume() const {return MasterVolume;};
	float GetMusicVolume() const {return MusicVolume;};
	float GetSfxVolume() const {return SFXVolume;};
	bool GetFullscreen() const {return bIsFullscreen;}; 
	int32 GetResolutionWidth() const;
	int32 GetResolutionHeight() const;
	EWindowMode::Type GetWindowMode() const;
	bool GetVSyncEnabled() const;
	float GetFrameRateLimit() const;
	
	// =========================================================
	// Setters
	// =========================================================
	void SetMasterVolume(float Value);
	void SetMusicVolume(float Value);
	void SetSfxVolume(float Value);
	void SetFullscreen(bool Enabled);
	void SetResolution(int32 Width, int32 Height);
	void SetFrameRateLimit(float Value);
	void SetWindowMode(EWindowMode::Type NewWindowMode);
	void SetVSyncEnabled(bool Enabled);
	
	// =========================================================
	// Initialization
	// =========================================================
	void Initialize(APlayerController* InPlayerController,TSubclassOf<USettingsWidget> InSettingsWidget,USoundClass* InMasterSoundClass,USoundClass* InMusicSoundClass,USoundClass* InSFXSoundClass,USoundMix* InSettingsSoundMix);
	
	void SetSettingsWidget(USettingsWidget* InSettingsWidget);
	void SetMainMenuManager(UMainMenuManager* InMainMenuManager);
	void SetSettingsSaveManager(USettingsSaveManager* InSettingsSaveManager);
	
	bool Validate() const;
	
	// =========================================================
	// Navigation
	// =========================================================
	void OpenGeneral();
	void OpenGraphics();
	void OpenAudio();
	void OpenControls();
	
	void GoBack();
	void ApplySettings();
	
	// =========================================================
	// Functionailty of panels
	// =========================================================
	
	void MasterVolumeChanged(float Volume);
	void SFXVolumeChanged(float Volume);
	void MusicVolumeChanged(float Volume);
	
	
	void ChangeWindowMode(const FString& NewWindowModeString);
	void ChangeResolution(const FString& NewResolution);
	void ChangeFrameRateLimit(const FString& NewFrameRateLimit);
	void ChangeVsync(bool bEnabled);
	
	
	// =========================================================
	// States
	// =========================================================
	ESettingsMenuStates GetCurrentState() const;
	
	// =========================================================
	// Unsaved Changes
	// =========================================================
	
	void MarkSettingsChanged();
	bool HasUnsavedChanges() const;
	void ClearUnsavedChanges();
	void RestoreSavedSettings();
	
	// =========================================================
	// Reset
	// =========================================================
	
	void ResetToDefaults();
	
	// =========================================================
	// Saved settings
	// =========================================================
	
	void CaptureSavedSettings();
	
private:
	// =========================================================
	// References
	// =========================================================
	UPROPERTY() TObjectPtr<APlayerController> PlayerController;

	UPROPERTY() TSubclassOf<USettingsWidget> SettingsWidgetClass;
	
	UPROPERTY() TObjectPtr<USettingsWidget> SettingsWidget;
	
	UPROPERTY() UMainMenuManager* MainMenuManager = nullptr;
	
	UPROPERTY() TObjectPtr<USettingsSaveManager> SaveManager;
	
	// =========================================================
	// State management
	// =========================================================

	
	void SetState(ESettingsMenuStates NewState);
	void ApplyState();
	
	ESettingsMenuStates CurrentState = ESettingsMenuStates::General;
	TArray<ESettingsMenuStates> StateStack;
	
	// =========================================================
	// Unsaved Changes
	// =========================================================
	
	bool bHasUnsavedChanges = false;
	
	// =========================================================
	// Unsaved Changes
	// =========================================================
	
	float SavedMasterVolume = 1.0f;
	float SavedMusicVolume = 1.0f;
	float SavedSFXVolume = 1.0f;
	
	int32 SavedResolutionWidth = 1920;
	int32 SavedResolutionHeight = 1080;
	
	EWindowMode::Type SavedWindowMode = EWindowMode::Windowed;
	
	bool SavedVsyncEnabled = false;
	
	float SavedFrameRateLimit = 60.0f;
	
	// =========================================================
	// Audio Values - Base values
	// =========================================================
	
	float MasterVolume = 1.0f;
	float SFXVolume = 1.0f;
	float MusicVolume = 1.0f;
	
	// =========================================================
	// Graphics Values - Base values
	// =========================================================
	
	bool bIsFullscreen = true;
	
	int32 ResolutionWidth = 1920;
	
	int32 ResolutionHeight = 1080;
	
	EWindowMode::Type WindowMode = EWindowMode::WindowedFullscreen;
	
	bool bVSyncEnabled = false;
	
	float FrameRateLimit = 60.0f;
	
protected:
	// =========================================================
	// Audio Reference
	// =========================================================
	
	UPROPERTY() TObjectPtr<USoundClass> MasterSoundClass;
	UPROPERTY() TObjectPtr<USoundClass> MusicSoundClass;
	UPROPERTY() TObjectPtr<USoundClass> SFXSoundClass;
	UPROPERTY() TObjectPtr<USoundMix> SettingsSoundMix;
};