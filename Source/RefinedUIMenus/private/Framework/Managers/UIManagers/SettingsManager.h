// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SettingsManager.generated.h"

class USettingsWidget;
class UMainMenuManager;
class USoundClass;
class USoundMix;

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
	// Initialization
	// =========================================================
	void Initialize(APlayerController* InPlayerController,TSubclassOf<USettingsWidget> InSettingsWidget,USoundClass* InMasterSoundClass,USoundClass* InMusicSoundClass,USoundClass* InSFXSoundClass,USoundMix* InSettingsSoundMix);
	
	void SetSettingsWidget(USettingsWidget* InSettingsWidget);
	void SetMainMenuManager(UMainMenuManager* InMainMenuManager);
	
	bool Validate() const;
	
	// =========================================================
	// Navigation
	// =========================================================
	void OpenGeneral();
	void OpenGraphics();
	void OpenAudio();
	void OpenControls();
	
	void GoBack();
	
	// =========================================================
	// Functionailty of panels
	// =========================================================
	
	void MasterVolumeChanged(float Volume);
	void SFXVolumeChanged(float Volume);
	
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
	
protected:
	// =========================================================
	// Audio Reference
	// =========================================================
	
	UPROPERTY() TObjectPtr<USoundClass> MasterSoundClass;
	UPROPERTY() TObjectPtr<USoundClass> MusicSoundClass;
	UPROPERTY() TObjectPtr<USoundClass> SFXSoundClass;
	UPROPERTY() TObjectPtr<USoundMix> SettingsSoundMix;
};


