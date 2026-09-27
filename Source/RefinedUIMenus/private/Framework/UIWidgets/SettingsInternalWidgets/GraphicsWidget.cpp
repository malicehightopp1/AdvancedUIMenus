// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/GraphicsWidget.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// =========================
	// Window Mode
	// =========================

	if (WindowModeComboBox)
	{
		WindowModeComboBox->AddOption(TEXT("Windowed"));
		WindowModeComboBox->AddOption(TEXT("Borderless"));
		WindowModeComboBox->AddOption(TEXT("Fullscreen"));

		WindowModeComboBox->OnSelectionChanged.AddDynamic(
			this,
			&UGraphicsWidget::OnWindowModeChanged
		);
	}


	// =========================
	// Resolution
	// =========================

	if (ResolutionComboBox)
	{
		ResolutionComboBox->AddOption(TEXT("1280 x 720"));
		ResolutionComboBox->AddOption(TEXT("1600 x 900"));
		ResolutionComboBox->AddOption(TEXT("1920 x 1080"));
		ResolutionComboBox->AddOption(TEXT("2560 x 1440"));
		ResolutionComboBox->AddOption(TEXT("3840 x 2160"));

		ResolutionComboBox->OnSelectionChanged.AddDynamic(
			this,
			&UGraphicsWidget::OnResolutionChanged
		);
	}


	// =========================
	// VSync
	// =========================

	if (VSyncCheckBox)
	{
		VSyncCheckBox->OnCheckStateChanged.AddDynamic(
			this,
			&UGraphicsWidget::OnVSyncChanged
		);
	}


	// =========================
	// Frame Rate
	// =========================

	if (FrameRateComboBox)
	{
		FrameRateComboBox->AddOption(TEXT("30 FPS"));
		FrameRateComboBox->AddOption(TEXT("60 FPS"));
		FrameRateComboBox->AddOption(TEXT("120 FPS"));
		FrameRateComboBox->AddOption(TEXT("144 FPS"));
		FrameRateComboBox->AddOption(TEXT("165 FPS"));
		FrameRateComboBox->AddOption(TEXT("240 FPS"));
		FrameRateComboBox->AddOption(TEXT("Unlimited"));

		FrameRateComboBox->OnSelectionChanged.AddDynamic(
			this,
			&UGraphicsWidget::OnFrameRateChanged
		);
	}
	if (SettingsManager)
	{
		RefreshUI();
	}
}

void UGraphicsWidget::SetSettingsManager(USettingsManager* NewSettingsManager)
{
	SettingsManager = NewSettingsManager;
	
	RefreshUI();
}

void UGraphicsWidget::RefreshUI()
{
	if (!SettingsManager)
    {
        return;
    }

    bIsRefreshingUI = true;

    if (WindowModeComboBox)
    {
        switch (SettingsManager->GetWindowMode())
        {
        case EWindowMode::Windowed:
            WindowModeComboBox->SetSelectedOption(TEXT("Windowed"));
            break;

        case EWindowMode::WindowedFullscreen:
            WindowModeComboBox->SetSelectedOption(TEXT("Borderless"));
            break;

        case EWindowMode::Fullscreen:
            WindowModeComboBox->SetSelectedOption(TEXT("Fullscreen"));
            break;

        default:
            break;
        }
    }
	
    if (ResolutionComboBox)
    {
        const int32 Width = SettingsManager->GetResolutionWidth();

        const int32 Height = SettingsManager->GetResolutionHeight();

        const FString Resolution = FString::Printf(TEXT("%d x %d"),Width,Height);

        ResolutionComboBox->SetSelectedOption(Resolution);
    }

    if (VSyncCheckBox)
    {
        VSyncCheckBox->SetIsChecked(SettingsManager->GetVSyncEnabled());
    }
	
    if (FrameRateComboBox)
    {
        const float FrameRate = SettingsManager->GetFrameRateLimit();

        FString FrameRateOption;

        if (FrameRate <= 0.0f)
        {
            FrameRateOption = TEXT("Unlimited");
        }
        else
        {
            FrameRateOption =FString::Printf(TEXT("%.0f FPS"),FrameRate);
        }

        FrameRateComboBox->SetSelectedOption(FrameRateOption);
    }


    bIsRefreshingUI = false;
}

void UGraphicsWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->ChangeResolution(SelectedItem);
}
void UGraphicsWidget::OnVSyncChanged(bool bIsChecked)
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->ChangeVsync(bIsChecked);
}
void UGraphicsWidget::OnFrameRateChanged(FString SelectedItem,ESelectInfo::Type SelectionType)
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->ChangeFrameRateLimit(SelectedItem);
}
void UGraphicsWidget::OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (!SettingsManager)
	{
		return;
	}

	SettingsManager->ChangeWindowMode(SelectedItem);
}
