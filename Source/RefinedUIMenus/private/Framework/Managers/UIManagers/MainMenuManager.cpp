// Fill out your copyright notice in the Description page of Project Settings.
#include "Framework/Managers/UIManagers/MainMenuManager.h"

#include "Blueprint/UserWidget.h"
#include "Framework/UIWidgets/MainMenuWidget.h"

void UMainMenuManager::Initialize(APlayerController* InPlayerController, TSubclassOf<UMainMenuWidget> InMainMenuWidgetClass)
{
	PlayerController = InPlayerController;
	MainMenuWidgetClass = InMainMenuWidgetClass;
	
	UE_LOG(LogTemp, Warning, TEXT("UI Manager was inited"));
	
	CreateWidgets();
	//BindWidgetEvents();
	
	CurrentState = EMainMenuState::Main;
	TargetState = EMainMenuState::Main;
	
	//UpdateInputMode();
}

void UMainMenuManager::CreateWidgets()
{
	if (!PlayerController) {return;}
	
	if (MainMenuWidgetClass)
	{
		 UE_LOG(LogTemp, Warning, TEXT("Create widget class called"));
		MainMenuWidget = CreateWidget<UMainMenuWidget>(PlayerController, MainMenuWidgetClass);
	}
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Main menu widget added to viewport"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Ui creation should be called"));
}
