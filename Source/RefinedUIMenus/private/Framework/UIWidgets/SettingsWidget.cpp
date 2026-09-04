// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"


void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

bool USettingsWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	return true;
	
}

void USettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if(BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &USettingsWidget::OnBackButtonPressed);
	}
	if (GeneralButton)
	{
		GeneralButton->OnClicked.AddDynamic(this, &USettingsWidget::OnGeneralClicked);
	}
	if (GraphicsButton)
	{
		GraphicsButton->OnClicked.AddDynamic(this, &USettingsWidget::OnGraphicsClicked);
	}
	if (AudioButton)
	{
		AudioButton->OnClicked.AddDynamic(this, &USettingsWidget::OnAudioClicked);
	}
	if (ControlsButton)
	{
		ControlsButton->OnClicked.AddDynamic(this, &USettingsWidget::OnControlsClicked);
	}
}

void USettingsWidget::SetSettingsManager(USettingsManager* NewSettingManager)
{
	SettingsManager = NewSettingManager;
}

void USettingsWidget::OnBackButtonPressed()
{
	if (SettingsManager)
	{
		SettingsManager->GoBack();
	}
}

void USettingsWidget::OnGeneralClicked()
{
	if (SettingsManager)
	{
		SettingsManager->OpenGeneral();
	}
}

void USettingsWidget::OnGraphicsClicked()
{
	if (SettingsManager)
	{
		SettingsManager->OpenGraphics();
	}
}

void USettingsWidget::OnAudioClicked()
{
	if (SettingsManager)
	{
		SettingsManager->OpenAudio();
	}
}

void USettingsWidget::OnControlsClicked()
{
	if (SettingsManager)
	{
		SettingsManager->OpenControls();
	}
}
