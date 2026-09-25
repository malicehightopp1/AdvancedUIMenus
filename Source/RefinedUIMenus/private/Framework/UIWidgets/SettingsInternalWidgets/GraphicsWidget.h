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

protected:

	virtual void NativeConstruct() override;

public:

	void SetSettingsManager(USettingsManager* NewSettingsManager);

	UFUNCTION()void RefreshUI();
protected:

	// =========================
	// Window Mode
	// =========================

	UPROPERTY(meta = (BindWidget))UComboBoxString* WindowModeComboBox;

	UFUNCTION()void OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	// =========================
	// Resolution
	// =========================

	UPROPERTY(meta = (BindWidget))UComboBoxString* ResolutionComboBox;

	UFUNCTION()void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);


	// =========================
	// VSync
	// =========================

	UPROPERTY(meta = (BindWidget))UCheckBox* VSyncCheckBox;

	UFUNCTION()void OnVSyncChanged(bool bIsChecked);


	// =========================
	// Frame Rate
	// =========================

	UPROPERTY(meta = (BindWidget))UComboBoxString* FrameRateComboBox;

	UFUNCTION()
	void OnFrameRateChanged(FString SelectedItem, ESelectInfo::Type SelectionType);


private:

	UPROPERTY()USettingsManager* SettingsManager;
};
