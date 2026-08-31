// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UCanvasPanel;
class UTextBlock;

UCLASS()
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct();
	virtual bool Initialize() override;
	
public:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TestTextBlock; 
	UPROPERTY(meta = (BindWidget)) UCanvasPanel* CanvasPanel;
	
};
