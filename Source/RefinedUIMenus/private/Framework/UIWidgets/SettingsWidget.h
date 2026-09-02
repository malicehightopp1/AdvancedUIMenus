// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

class USettingsManager;
class UTextBlock;
class UCanvasPanel;

UCLASS()
class USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> TestingBlock;
};
