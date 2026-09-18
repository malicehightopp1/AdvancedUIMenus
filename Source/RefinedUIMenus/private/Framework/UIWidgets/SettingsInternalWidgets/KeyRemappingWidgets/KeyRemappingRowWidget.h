// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyRemappingRowWidget.generated.h"

class UInputMappingManager;
class UInputAction;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class UKeyRemappingRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,const FPointerEvent& InMouseEvent) override;

	void SetInputAction(UInputAction* InInputAction);

	void SetActionName(const FText& InName);

	void SetMappingName(FName InMappingName);

	void SetRemappingManager(UInputMappingManager* InRemappingManager);

	void RefreshCurrentKey();

protected:

	UFUNCTION()
	void OnChangeButtonClicked();

	void BeginKeyRemap();

	void CancelKeyRemap();

	void ApplyNewKey(const FKey& NewKey);

protected:

	UPROPERTY()
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY()TObjectPtr<UInputMappingManager> RemappingManager;

	UPROPERTY()FName MappingName;

	UPROPERTY()bool bWaitingForKey = false;

	UPROPERTY(meta = (BindWidget))TObjectPtr<UTextBlock> ActionNameText;

	UPROPERTY(meta = (BindWidget))TObjectPtr<UTextBlock> CurrentKeyText;

	UPROPERTY(meta = (BindWidget))TObjectPtr<UTextBlock> StatusText;

	UPROPERTY(meta = (BindWidget))TObjectPtr<UButton> ChangeButton;
};
