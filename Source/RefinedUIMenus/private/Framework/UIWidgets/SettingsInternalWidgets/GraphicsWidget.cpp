// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/GraphicsWidget.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"

void UGraphicsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (WindowModeComboBox)
	{
		WindowModeComboBox->AddOption(TEXT("Windowed"));
		WindowModeComboBox->AddOption(TEXT("Borderless"));
		WindowModeComboBox->AddOption(TEXT("Fullscreen"));
		
		WindowModeComboBox->OnSelectionChanged.AddDynamic(this, &UGraphicsWidget::OnWindowModeChanged);
		
		WindowModeComboBox->bIsFocusable = true;
	}
}

void UGraphicsWidget::SetSettingsManager(USettingsManager* NewSettingsManager)
{
	SettingsManager = NewSettingsManager; 
	
	if (!SettingsManager)
	{
		return;
	}
}

void UGraphicsWidget::OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (!SettingsManager)
	{
		return;
	}
	if (SelectedItem == TEXT("Windowed"))
	{
		SettingsManager->ChangeWindowMode(EWindowMode::Windowed);
	}
	else if (SelectedItem == TEXT("Borderless"))
	{
		SettingsManager->ChangeWindowMode(EWindowMode::WindowedFullscreen);
	}
	else if (SelectedItem == TEXT("Fullscreen"))
    {
		SettingsManager->ChangeWindowMode(EWindowMode::Fullscreen);
    }
}
