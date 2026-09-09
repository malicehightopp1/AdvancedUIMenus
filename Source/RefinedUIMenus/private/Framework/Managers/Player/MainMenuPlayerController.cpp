// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/Player/MainMenuPlayerController.h"

#include "Framework/GameModes/MainMenuGameMode.h"
#include "Framework/Services/ServiceLocatorSubsystem.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "InputCoreTypes.h"
#include "AI/NavigationSystemBase.h"
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

	USettingsManager* SettingsManager = Services->GetSettingsManager();
	
	MenuManager->Initialize( this, GameMode->MainMenuWidgetClass, GameMode->SettingsWidgetClass);
	
	if (!SettingsManager)
	{
		return;
	}
	
	SettingsManager->Initialize(this, GameMode->SettingsWidgetClass);
}

void AMainMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &AMainMenuPlayerController::HandleAnyKey);
}

void AMainMenuPlayerController::HandleAnyKey()
{
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);
	if (!Services)
	{
		return;
	}
	UMainMenuManager* MenuManager = Services->GetMainMenuManager();
	if (MenuManager)
	{
		MenuManager->PressAnyKey();
	}
}
