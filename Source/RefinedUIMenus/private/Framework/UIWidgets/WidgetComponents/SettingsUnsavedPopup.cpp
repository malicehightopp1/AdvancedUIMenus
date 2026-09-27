// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/WidgetComponents/SettingsUnsavedPopup.h"

#include "AudioButtonBase.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "Framework/UIWidgets/SettingsWidget.h"

void USettingsUnsavedPopup::SetSettingsManager(USettingsManager* InSettingsManager)
{
	SettingsManager = InSettingsManager;
}

void USettingsUnsavedPopup::SetSettingsWidget(class USettingsWidget* InSettingsWidget)
{
	SettingsWidget = InSettingsWidget;
}

void USettingsUnsavedPopup::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	if (SaveGameButton)
	{
		SaveGameButton->OnClicked.AddDynamic(this,&USettingsUnsavedPopup::OnSaveClicked);
	}

	if (DontSaveGameButton)
	{
		DontSaveGameButton->OnClicked.AddDynamic(this,&USettingsUnsavedPopup::OnDontSaveClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this,&USettingsUnsavedPopup::OnCancelClicked);
	}
}

void USettingsUnsavedPopup::OnSaveClicked()
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->ApplySettings();

	SetVisibility(ESlateVisibility::Hidden);

	SettingsManager->GoBack();
}

void USettingsUnsavedPopup::OnDontSaveClicked()
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->RestoreSavedSettings();

	if (SettingsWidget)
	{
		SettingsWidget->RefreshsettingsUI();
	}

	SetVisibility(ESlateVisibility::Hidden);

	SettingsManager->GoBack();
}

void USettingsUnsavedPopup::OnCancelClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

