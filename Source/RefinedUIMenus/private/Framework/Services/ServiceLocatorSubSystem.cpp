// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Services/ServiceLocatorSubSystem.h"

#include "Framework/Managers/UIManagers/MainMenuManager.h"

void UServiceLocatorSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	MainMenuManager = NewObject<UMainMenuManager>(this); //creating the main menu manager, "this" is basically saying that the service locator owns the manager
	
	UE_LOG(LogTemp, Warning, TEXT("Service locator initilized"))
}

void UServiceLocatorSubSystem::Deinitialize()
{
	Super::Deinitialize();
	
	MainMenuManager = nullptr;
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

UMainMenuManager* UServiceLocatorSubSystem::GetMainMenuManager() const
{
	return MainMenuManager;
}
