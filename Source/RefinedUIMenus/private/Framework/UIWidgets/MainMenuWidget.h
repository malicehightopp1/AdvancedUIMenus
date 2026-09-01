// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class USizeBox;
class UVerticalBox;
class UBorder;
class UOverlay;
class UButton;
class UCanvasPanel;
class UTextBlock;

UCLASS(Blueprintable)
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct();
	virtual bool Initialize() override;
	virtual void NativeOnInitialized() override;
	
public:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> TestTextBlock; 
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCanvasPanel> CanvasPanel;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> ButtonVerticalBoxHolder;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> StartGameButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> SettingsButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> QuitButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USizeBox> ButtonSizeBox;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UOverlay> UiHolder;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UBorder> BackgroundBorder;
};
