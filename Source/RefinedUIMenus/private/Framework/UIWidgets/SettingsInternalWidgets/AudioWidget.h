// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AudioWidget.generated.h"

class USettingsManager;
class UTextBlock;
class USlider;

UCLASS()
class UAudioWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
	//Master volume
	UFUNCTION() void OnMasterVolumeChanged(float Value);
	
	UPROPERTY(meta = (BindWidget)) USlider* MasterVolumeSlider;
	UPROPERTY(meta = (BindWidget)) UTextBlock* MasterVolumeTextBlock;
	
	//SFX volume
	UFUNCTION() void OnSFXVolumeChanged(float Value);
	
	UPROPERTY(meta = (BindWidget)) USlider* SFXVolumeSlider;
	UPROPERTY(meta = (BindWidget)) UTextBlock* SFXVolumeTextBlock;
	
	//References
	UFUNCTION() void SetSettingsManager(USettingsManager* InSettingsManager);
	UPROPERTY() USettingsManager* SettingsManager;
	
private:
	UPROPERTY(EditDefaultsOnly) float StartingValue = 0.5;
};

