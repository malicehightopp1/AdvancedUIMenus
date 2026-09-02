// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/Player/MainMenuPlayerController.h"

#include "Framework/GameModes/MainMenuGameMode.h"
#include "Framework/Services/ServiceLocatorSubsystem.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);

	if (!Services)
	{
		return;
	}

	AMainMenuGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainMenuGameMode>();

	if (!GameMode)
	{
		return;
	}

	UMainMenuManager* MenuManager = Services->GetMainMenuManager();

	if (!MenuManager)
	{
		return;
	}

	MenuManager->Initialize( this, GameMode->MainMenuWidgetClass, GameMode->SettingsWidgetClass);
	
	USettingsManager* SettingsManager = Services->GetSettingsManager();
	
	if (!SettingsManager)
	{
		return;
	}
	
	SettingsManager->Initialize(this);
}
