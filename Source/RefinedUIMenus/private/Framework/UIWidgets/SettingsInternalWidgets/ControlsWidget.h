// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsWidget.generated.h"

class UInputMappingManager;
class UKeyRemappingWidget;
/**
 * 
 */
UCLASS()
class UControlsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetInputMappingManager(UInputMappingManager* InInputMappingManager);

protected:

	UPROPERTY(meta = (BindWidget))TObjectPtr<UKeyRemappingWidget> KeyRemappingWidget;

private:

	UPROPERTY()TObjectPtr<UInputMappingManager> InputMappingManager;
};
