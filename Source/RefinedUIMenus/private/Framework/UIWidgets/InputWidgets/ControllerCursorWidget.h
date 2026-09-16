// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControllerCursorWidget.generated.h"

class UCanvasPanel;
class UImage;

UCLASS()
class UControllerCursorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCanvasPanel> CanvasPanel;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> CursorImage;

};
