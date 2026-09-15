// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/GraphicsWidget.h"

#include "Components/CheckBox.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"

void UGraphicsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (FullscreenBox)
	{
		FullscreenBox->OnCheckStateChanged.RemoveDynamic(this, &UGraphicsWidget::FullScreenCheckChanged);
		
		FullscreenBox->OnCheckStateChanged.AddDynamic(this, &UGraphicsWidget::FullScreenCheckChanged);
	}
}

void UGraphicsWidget::SetSettingsManager(USettingsManager* NewSettingsManager)
{
	SettingsManager = NewSettingsManager; 
}

void UGraphicsWidget::FullScreenCheckChanged(bool BIsChecked)
{
	if (!FullscreenBox || !SettingsManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Settings manager or fullscreen box"));
		return;
	}
	if (FullscreenBox)
	{
		if (BIsChecked)
		{
			SettingsManager->ChangefullScreen(true);
			UE_LOG(LogTemp, Warning, TEXT("Fullscreen Active"));
		}
		else
		{
			SettingsManager->ChangefullScreen(false);
			UE_LOG(LogTemp, Warning, TEXT("Windowed Active"));
		}
	}
}
