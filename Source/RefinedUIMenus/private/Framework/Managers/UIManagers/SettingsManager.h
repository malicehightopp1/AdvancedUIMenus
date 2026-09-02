// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SettingsManager.generated.h"

class USettingsWidget;
/**
 * 
 */
UCLASS()
class USettingsManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(APlayerController* InPlayerController); //called for init setup
	
private:
	UPROPERTY() TObjectPtr<APlayerController> PlayerController;

	UPROPERTY() TSubclassOf<USettingsWidget> SettingsWidgetClass;
	
	UPROPERTY() TObjectPtr<USettingsWidget> SettingsWidget;
};
