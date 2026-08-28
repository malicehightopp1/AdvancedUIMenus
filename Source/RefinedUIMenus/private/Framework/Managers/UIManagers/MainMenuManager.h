// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MainMenuManager.generated.h"

class UMainMenuWidget;
UENUM(BlueprintType)
enum class EMainMenuState : uint8
{
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
	void Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass); //called for init setup
	
	// void OpenMainMenu();
	// void OpenSettings();
	// void OpenCredits();
	// void GoBack();
	
	//void StartGame();
	//void QuitGame();
	
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
	
	//void SetState(EMainMenuState NewState);
	
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
	UPROPERTY() TSubclassOf<UMainMenuWidget> SettingsWidgetClass;
	
	UPROPERTY() TObjectPtr<UMainMenuWidget> MainMenuWidget;
	UPROPERTY() TObjectPtr<UMainMenuManager> SettingsWidget;
};
