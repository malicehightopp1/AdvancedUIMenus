// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/SavingManager/SettingsSaveManager.h"

#include "SettingsSaveGame.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "Kismet/GameplayStatics.h"

void USettingsSaveManager::Initialize(USettingsManager* InSettingsManager)
{
	SettingsManager = InSettingsManager;
	
	LoadSettings();
	UE_LOG(LogTemp, Warning, TEXT("Saving manager init was called"))
}

void USettingsSaveManager::SaveSettings()
{
	if (!SettingsManager)
	{
		return;
	}
	SettingsSaveGame = Cast<USettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass()));
	
	if (!SettingsSaveGame)
	{
		return;
	}

	//Audio
	SettingsSaveGame->MasterVolume = SettingsManager->GetMasterVolume();
	SettingsSaveGame->MusicVolume = SettingsManager->GetMusicVolume();
	SettingsSaveGame->SFXVolume = SettingsManager->GetSfxVolume();
	SettingsSaveGame->bFullscreen = SettingsManager->GetFullscreen();
	
	//Graphics
	SettingsSaveGame->ResolutionWidth = SettingsManager->GetResolutionWidth();
	SettingsSaveGame->ResolutionHeight = SettingsManager->GetResolutionHeight();
	SettingsSaveGame->WindowMode = static_cast<int32>(SettingsManager->GetWindowMode());
	SettingsSaveGame->bVSyncEnabled = SettingsManager->GetVSyncEnabled();
	SettingsSaveGame->FrameRateLimit = SettingsManager->GetFrameRateLimit();
	
	UGameplayStatics::SaveGameToSlot(SettingsSaveGame, SaveSlotName, 0);
	UE_LOG(LogTemp, Warning, TEXT("Saving manager called its Save settings function"))
}

void USettingsSaveManager::LoadSettings()
{
	if (!SettingsManager)
	{
		return;
	}
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		return;
	}
	
	SettingsSaveGame = Cast<USettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
		
	if (!SettingsSaveGame)
	{
		return;
	}

	//Audio
	SettingsManager->SetMasterVolume(SettingsSaveGame->MasterVolume);
	SettingsManager->SetMusicVolume(SettingsSaveGame->MusicVolume);
	SettingsManager->SetSfxVolume(SettingsSaveGame->SFXVolume);
	
	//Graphics
	SettingsManager->SetResolution(SettingsSaveGame->ResolutionWidth, SettingsSaveGame->ResolutionHeight);
	SettingsManager->SetWindowMode(static_cast<EWindowMode::Type>(SettingsSaveGame->WindowMode));
	SettingsManager->SetVSyncEnabled(SettingsSaveGame->bVSyncEnabled);
	SettingsManager->SetFrameRateLimit(SettingsSaveGame->FrameRateLimit);
	
	UE_LOG(LogTemp, Warning, TEXT("Music Loaded: %f"), SettingsSaveGame->MusicVolume);
	
	UE_LOG(LogTemp, Warning, TEXT("Saving manager called its load settings function"))
}
