// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsWidget.generated.h"

class UComboBoxString;
class USettingsManager;
class UCheckBox;

UCLASS()
class UGraphicsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION() void SetSettingsManager(USettingsManager* NewSettingsManager);
	
	UFUNCTION() void OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UComboBoxString> WindowModeComboBox;
	
	//references
	UPROPERTY() TObjectPtr<USettingsManager> SettingsManager;
};
