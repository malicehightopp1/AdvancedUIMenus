// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Managers/GameInstances/MainMenuInstance.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"

void UMainMenuInstance::Init()
{
	Super::Init();
	
	MainMenuManager = NewObject<UMainMenuManager>(this); //creates main menu manager object of init()
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuManager::Init() called"));
}

void UMainMenuInstance::Shutdown()
{
	Super::Shutdown();
	
	MainMenuManager = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuManager::Shutdown() called"));
}

UMainMenuManager* UMainMenuInstance::GetMainMenuManager() const
{
	return MainMenuManager;
}
