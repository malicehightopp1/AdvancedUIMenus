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
	float GetMasterVolume() const {return MasterVolume;};
	void SetMasterVolume(float Value);
	
	float GetMusicVolume() const {return MusicVolume;};
	void SetMusicVolume(float Value);
	
	float GetSfxVolume() const {return SFXVolume;};
	void SetSfxVolume(float Value);
	
	bool GetFullscreen() const {return bIsFullscreen;}; 
	void SetFullscreen(bool Enabled);
	
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
	
	void ChangefullScreen(bool IsInFullscreen);
	
	// =========================================================
	// States
	// =========================================================
	ESettingsMenuStates GetCurrentState() const;
	
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
	// States
	// =========================================================
	
	void SetState(ESettingsMenuStates NewState);
	void ApplyState();
	
	ESettingsMenuStates CurrentState = ESettingsMenuStates::General;
	TArray<ESettingsMenuStates> StateStack;
	
	// =========================================================
	// Audio Values
	// =========================================================
	
	float MasterVolume = 1.0f;
	float SFXVolume = 1.0f;
	float MusicVolume = 1.0f;
	
	// =========================================================
	// Graphics Values
	// =========================================================
	
	bool bIsFullscreen = true;
	
protected:
	// =========================================================
	// Audio Reference
	// =========================================================
	
	UPROPERTY() TObjectPtr<USoundClass> MasterSoundClass;
	UPROPERTY() TObjectPtr<USoundClass> MusicSoundClass;
	UPROPERTY() TObjectPtr<USoundClass> SFXSoundClass;
	UPROPERTY() TObjectPtr<USoundMix> SettingsSoundMix;
};