// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsWidget.generated.h"

class USettingsManager;
class UCheckBox;

UCLASS()
class UGraphicsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION() void SetSettingsManager(USettingsManager* NewSettingsManager);
	UFUNCTION() void FullScreenCheckChanged(bool bIsChecked);
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCheckBox> FullscreenBox;
	
	//references
	UPROPERTY() TObjectPtr<USettingsManager> SettingsManager;
};
