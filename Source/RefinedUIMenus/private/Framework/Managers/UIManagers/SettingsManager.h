// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SettingsManager.generated.h"

class USettingsWidget;

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
	void Initialize(APlayerController* InPlayerController, TSubclassOf<USettingsWidget> InSettingsWidget); //called for init setup
	
	bool Validate() const;
	
	// =========================================================
	// Navigation
	// =========================================================
	void OpenGeneral();
	void OpenGraphics();
	void OpenAudio();
	void OpenControls();
	
	void GoBack();
	
	void ExittingSettings();
	
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
	
	// =========================================================
	// States
	// =========================================================
	
	void SetState(ESettingsMenuStates NewState);
	void ApplyState();
	
	ESettingsMenuStates CurrentState = ESettingsMenuStates::General;
	TArray<ESettingsMenuStates> StateStack;
};

