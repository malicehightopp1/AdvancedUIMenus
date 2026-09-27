// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsUnsavedPopup.generated.h"

class UAudioButtonBase;
class USettingsManager;
/**
 * 
 */
UCLASS()
class USettingsUnsavedPopup : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetSettingsManager(USettingsManager* InSettingsManager);

	void SetSettingsWidget(class USettingsWidget* InSettingsWidget);

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY()USettingsManager* SettingsManager = nullptr;

	UPROPERTY()class USettingsWidget* SettingsWidget = nullptr;

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioButtonBase> SaveGameButton;

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioButtonBase> DontSaveGameButton = nullptr;

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioButtonBase> CancelButton = nullptr;

	UFUNCTION()void OnSaveClicked();

	UFUNCTION()void OnDontSaveClicked();

	UFUNCTION()void OnCancelClicked();
};
