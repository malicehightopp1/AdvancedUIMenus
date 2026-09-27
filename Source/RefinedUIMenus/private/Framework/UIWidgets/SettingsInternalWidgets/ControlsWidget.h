// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsWidget.generated.h"

class UTextBlock;
class UAudioButtonBase;
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
	
	virtual void NativeConstruct() override;
	void SetInputMappingManager(UInputMappingManager* InInputMappingManager);

	UFUNCTION() void OnSavedclicked();
	UFUNCTION() void OnDontSaveclicked();
	UFUNCTION() void OnResetAllClicked();
	UFUNCTION() void RefreshUnsavedState();
	
protected:

	UPROPERTY(meta = (BindWidget))TObjectPtr<UKeyRemappingWidget> KeyRemappingWidget;

private:

	UPROPERTY()TObjectPtr<UInputMappingManager> InputMappingManager;
	
	UPROPERTY(meta = (BindWidget)) UAudioButtonBase* SaveButton;
	UPROPERTY(meta = (BindWidget)) UAudioButtonBase* DontSaveButton;
	UPROPERTY(meta = (BindWidget)) UAudioButtonBase* ResetAllButton;
	
	UPROPERTY(meta = (BindWidget)) UTextBlock* UnSavedChanges;

	
};
