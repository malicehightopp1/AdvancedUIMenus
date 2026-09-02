// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/UIManagers/SettingsManager.h"

#include "Blueprint/UserWidget.h"
#include "Framework/UIWidgets/SettingsWidget.h"

void USettingsManager::Initialize(APlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
	
		
	UE_LOG(LogTemp, Warning, TEXT("Settings Manager was inited"));
}

