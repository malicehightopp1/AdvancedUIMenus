// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Services/ServiceLocatorSubSystem.h"

#include "Framework/Managers/Player/PlayerCamera/MainMenuCamera.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"

void UServiceLocatorSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	MainMenuManager = NewObject<UMainMenuManager>(this); //creating the main menu manager, "this" is basically saying that the service locator owns the manager
	SettingsManager = NewObject<USettingsManager>(this);
	
	UE_LOG(LogTemp, Warning, TEXT("Service locator initilized"))
}

void UServiceLocatorSubSystem::Deinitialize()
{
	Super::Deinitialize();
	
	MainMenuManager = nullptr;
	SettingsManager = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Service locator DeInitilized"))
}

UServiceLocatorSubSystem* UServiceLocatorSubSystem::Get(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}
	
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return nullptr;
	}
	UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	return GameInstance->GetSubsystem<UServiceLocatorSubSystem>();
}

#pragma region Getters
UMainMenuManager* UServiceLocatorSubSystem::GetMainMenuManager() const
{
	return MainMenuManager;
}

USettingsManager* UServiceLocatorSubSystem::GetSettingsManager() const
{
	return SettingsManager;
}

#pragma endregion Getters
