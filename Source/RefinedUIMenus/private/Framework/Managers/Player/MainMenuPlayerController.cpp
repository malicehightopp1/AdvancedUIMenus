// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/Player/MainMenuPlayerController.h"

#include "Framework/GameModes/MainMenuGameMode.h"
#include "Framework/Managers/GameInstances/MainMenuInstance.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//Making sure if no game instance dont run
	UMainMenuInstance* GameInstance = GetGameInstance<UMainMenuInstance>();
	
	if (!GameInstance)
	{
		return;
	}
	
	AMainMenuGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainMenuGameMode>();
	
	if (!GameMode)
	{
		return;
	}
	
	//if theres a manager found init it
	UMainMenuManager* MenuManager = GameInstance->GetMainMenuManager();
	
	if (MenuManager)
	{
		MenuManager->Initialize(this, GameMode->MainMenuWidgetClass);
	}
}
