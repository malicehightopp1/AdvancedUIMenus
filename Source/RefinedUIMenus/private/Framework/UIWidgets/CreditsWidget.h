// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsWidget.generated.h"


class UMainMenuManager;
class UAudioButtonBase;
class UBorder;
class UTextBlock;
class UVerticalBox;
class UCanvasPanel;

UCLASS()
class UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION() void FocusBackButton();
	
	UFUNCTION() void SetMainMenuManager(UMainMenuManager* InMainMenuManager);

	UFUNCTION() void OnBackButtonPressed();

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCanvasPanel> BasePanel; 
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> VerticalBox;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> CreditsName;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UBorder> BackgroundComp;
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioButtonBase> BackButton;
	
	UPROPERTY() TObjectPtr<UMainMenuManager> MainMenuManager; 
};
