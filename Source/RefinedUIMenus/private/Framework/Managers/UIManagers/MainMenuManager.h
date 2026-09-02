// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MainMenuManager.generated.h"

class USettingsWidget;
class UMainMenuWidget;
UENUM(BlueprintType)
enum class EMainMenuState : uint8
{
	Playing,
	Main,
	Settings,
	Graphics,
	Audio,
	Controls,
	Credits
};
UCLASS()
class UMainMenuManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass, TSubclassOf<USettingsWidget> InSettingsWidgetClass); //called for init setup
	
	//UFUNCTION() void OpenMainMenu();
	UFUNCTION() void StartGame();
	UFUNCTION()void OpenSettings();
	//UFUNCTION()void OpenCredits();
	UFUNCTION()void QuitGame();
	// void GoBack();
	
	
	//states
	//EMainMenuState GetCurrentState() const;
	
private:
	// =========================================================
	// Initialization
	// =========================================================
	
	void CreateWidgets();
	//void BindWidgetEvents();
	
	// =========================================================
	// states
	// =========================================================
	
	UFUNCTION() void SetState(EMainMenuState NewState);
	UFUNCTION() EMainMenuState GetCurrentState() const;
	
	EMainMenuState CurrentState = EMainMenuState::Main;
	EMainMenuState TargetState = EMainMenuState::Main;
	
	bool bIsTransitioning = false;
	
	// =========================================================
	// transitions
	// =========================================================
	
	//void BeginTransition();
	//void EndTransition();
	
	// =========================================================
	// Input
	// =========================================================
	
	//void UpdateInputMode();
	//void SetupUIInputMode();
	
	// =========================================================
	// Context
	// =========================================================
	
	UPROPERTY() TObjectPtr<APlayerController> PlayerController;
	
	// =========================================================
	// Widgets
	// =========================================================
	
	UPROPERTY() TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	
	UPROPERTY() TObjectPtr<UMainMenuWidget> MainMenuWidget;
	
	//settings widgets
	UPROPERTY() TSubclassOf<USettingsWidget> SettingsWidgetClass;
	
	UPROPERTY() TObjectPtr<USettingsWidget> SettingsWidget;
};
