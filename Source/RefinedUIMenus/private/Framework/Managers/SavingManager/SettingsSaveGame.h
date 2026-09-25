// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.generated.h"


UCLASS()
class USettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY() float MasterVolume = 1.0f;
	UPROPERTY() float MusicVolume = 1.0f;
	UPROPERTY() float SFXVolume = 1.0f;
	
	UPROPERTY() bool bFullscreen = true;
	
	UPROPERTY() int32 ResolutionWidth = 1920;
	UPROPERTY() int32 ResolutionHeight = 1080;
	UPROPERTY() int32 WindowMode = 1;
	UPROPERTY() bool bVSyncEnabled = false;
	UPROPERTY() float FrameRateLimit = 60.0f;
};
