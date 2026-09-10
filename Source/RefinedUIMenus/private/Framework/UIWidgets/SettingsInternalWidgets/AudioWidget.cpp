// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/AudioWidget.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"

void UAudioWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UAudioWidget::OnMasterVolumeChanged);
		OnMasterVolumeChanged(StartingValue);
	}
	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->OnValueChanged.AddDynamic(this, &UAudioWidget::OnSFXVolumeChanged);
		OnSFXVolumeChanged(StartingValue);
	}
}

void UAudioWidget::OnMasterVolumeChanged(float Value)
{
	if (SettingsManager)
	{
		SettingsManager->MasterVolumeChanged(Value);
	}
	if (MasterVolumeTextBlock)
	{
		int32 VolumePercent = FMath::RoundToInt(Value * 100.0f);
		MasterVolumeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Master Volume: %.d%%"), VolumePercent)));
	}
}

void UAudioWidget::OnSFXVolumeChanged(float Value)
{
	if (SettingsManager)
	{
		SettingsManager->SFXVolumeChanged(Value);
	}
	if (SFXVolumeTextBlock)
	{
		int32 VolumePercent = FMath::RoundToInt(Value * 100.0f);
		SFXVolumeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("SFX Volume: %.d%%"), VolumePercent)));
	}
}

void UAudioWidget::SetSettingsManager(USettingsManager* InSettingsManager)
{
	SettingsManager = InSettingsManager;
}
