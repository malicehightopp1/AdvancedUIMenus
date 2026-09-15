// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SettingsSaveManager.generated.h"

class USettingsManager;
class USettingsSaveGame;

UCLASS()
class USettingsSaveManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(USettingsManager* InSettingsManager);
	
	void SaveSettings();
	void LoadSettings();
	
private:
	UPROPERTY() USettingsManager* SettingsManager;
	UPROPERTY() USettingsSaveGame* SettingsSaveGame;
	
	FString SaveSlotName = TEXT("SettingsSlot");
};
