// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsWidget.h"

#include "Components/Button.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "SettingsInternalWidgets/AudioWidget.h"
#include "SettingsInternalWidgets/GraphicsWidget.h"
#include "WidgetComponents/AudioButtonBase.h"
#include "WidgetComponents/SettingsUnsavedPopup.h"


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
		BackButton->IsFocusable = true;
	}
	if (GeneralButton)
	{
		GeneralButton->OnClicked.AddDynamic(this, &USettingsWidget::OnGeneralClicked);
		GeneralButton->IsFocusable = true;
	}
	if (GraphicsButton)
	{
		GraphicsButton->OnClicked.AddDynamic(this, &USettingsWidget::OnGraphicsClicked);
		GraphicsButton->IsFocusable = true;
	}
	if (AudioButton)
	{
		AudioButton->OnClicked.AddDynamic(this, &USettingsWidget::OnAudioClicked);
		AudioButton->IsFocusable = true;
	}
	if (ControlsButton)
	{
		ControlsButton->OnClicked.AddDynamic(this, &USettingsWidget::OnControlsClicked);
		ControlsButton->IsFocusable = true;
	}
	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &USettingsWidget::OnApplyButtonClicked);
		ApplyButton->IsFocusable = true;
	}
	if (ResetToDefaultButton)
	{
		ResetToDefaultButton->OnClicked.AddDynamic(this, &USettingsWidget::OnResetToDefaultClicked);
		ResetToDefaultButton->IsFocusable = true;
	}
}

void USettingsWidget::SetSettingsManager(USettingsManager* NewSettingManager)
{
	SettingsManager = NewSettingManager;

	if (AudioWidget)
	{
		AudioWidget->SetSettingsManager(SettingsManager);
	}
	if (GraphicsWidget)
	{
		GraphicsWidget->SetSettingsManager(SettingsManager);
	}
	if (UnsavedPopup)
	{
		UnsavedPopup->SetSettingsManager(SettingsManager);
		UnsavedPopup->SetSettingsWidget(this);
	}
}

void USettingsWidget::SetInputMappingManager(UInputMappingManager* NewInputMappingManager)
{
	InputMappingManager = NewInputMappingManager;
}

UControlsWidget* USettingsWidget::GetControlsWidget() const
{
	return ControlsWidget;
}

void USettingsWidget::OnBackButtonPressed()
{
	if (!SettingsManager)
	{
		return;
	}

	if (SettingsManager->HasUnsavedChanges())
	{
		UE_LOG(LogTemp, Log, TEXT("Unsaved changes has been focused"));
		ShowUnsavedChangesPopup();
		return;
	}
	
	SettingsManager->GoBack();
}

void USettingsWidget::OnApplyButtonClicked()
{
	if (SettingsManager)
	{
		UE_LOG(LogTemp, Log, TEXT("Apply settings button has been clicked"));
		SettingsManager->ApplySettings();
	}
}

void USettingsWidget::SetGeneralButtonFocus()
{
	if (GeneralButton)
	{
		GeneralButton->SetKeyboardFocus();
		UE_LOG(LogTemp, Log, TEXT("General button has been focused"));
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

void USettingsWidget::OnResetToDefaultClicked()
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->ResetToDefaults();
	
	RefreshsettingsUI();
}

void USettingsWidget::RefreshsettingsUI()
{
	if (!SettingsManager)
	{
		return;
	}

	if (AudioWidget)
	{
		AudioWidget->RefreshUI();
	}

	if (GraphicsWidget)
	{
		GraphicsWidget->RefreshUI();
	}
}

void USettingsWidget::ShowUnsavedChangesPopup()
{
	UnsavedPopup->SetVisibility(ESlateVisibility::Visible);
}
