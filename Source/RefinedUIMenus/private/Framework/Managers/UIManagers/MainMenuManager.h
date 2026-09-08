// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MainMenuManager.generated.h"

class USettingsManager;
class USettingsWidget;
class UMainMenuWidget;

//Main menu states
UENUM(BlueprintType)
enum class EMainMenuState : uint8
{
	Idle,
	Playing,
	Main,
	Settings,
	Credits
};

UCLASS()
class UMainMenuManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass, TSubclassOf<USettingsWidget> InSettingsWidgetClass); //called for init setup
	
	bool ValidateWidgets() const;
	
	UFUNCTION() void StartGame();
	UFUNCTION()void OpenSettings();
	//UFUNCTION()void OpenCredits();
	UFUNCTION()void QuitGame();
	void GoBack();
	void OpenMainMenu();
	
	void PressAnyKey();
private:
	// =========================================================
	// Initialization
	// =========================================================
	
	void CreateWidgets();
	//void BindWidgetEvents();
	
	// =========================================================
	// states
	// =========================================================
	
	void SetState(EMainMenuState NewState);
	void ApplyState();
	EMainMenuState GetCurrentState() const;
	
	EMainMenuState CurrentState = EMainMenuState::Main;
	TArray<EMainMenuState> StateStack; //so the back button has a history of what states and menus the player has gone through
	
	bool bIsTransitioning = false;
	
	// =========================================================
	// transitions
	// =========================================================
	
	//void BeginTransition();
	//void EndTransition();
	
	// =========================================================
	// Input
	// =========================================================
	
	void UpdateInputMode();
	void SetupUIInputMode();
	void SetupGameInputMode();
	
	// =========================================================
	// Context
	// =========================================================
	
	UPROPERTY() TObjectPtr<APlayerController> PlayerController;
	
	// =========================================================
	// Widgets
	// =========================================================
	
	//Main menu widgets
	UPROPERTY() TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	
	UPROPERTY() TObjectPtr<UMainMenuWidget> MainMenuWidget;
	
	//settings widgets
	UPROPERTY() TSubclassOf<USettingsWidget> SettingsWidgetClass;
	UPROPERTY() TObjectPtr<USettingsWidget> SettingsWidget;
};
