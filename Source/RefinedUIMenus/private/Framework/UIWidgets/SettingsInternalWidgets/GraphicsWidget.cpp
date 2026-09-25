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

	// =========================
	// Window Mode
	// =========================

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

	// =========================
	// Resolution
	// =========================

	if (ResolutionComboBox)
	{
		const int32 Width = SettingsManager->GetResolutionWidth();
		const int32 Height = SettingsManager->GetResolutionHeight();

		const FString Resolution = FString::Printf(TEXT("%d x %d"), Width, Height);

		ResolutionComboBox->SetSelectedOption(Resolution);
	}

	// =========================
	// VSync
	// =========================

	if (VSyncCheckBox)
	{
		VSyncCheckBox->SetIsChecked(
			SettingsManager->GetVSyncEnabled()
		);
	}

	// =========================
	// Frame Rate
	// =========================

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
			FrameRateOption = FString::Printf(TEXT("%.0f FPS"), FrameRate);
		}

		FrameRateComboBox->SetSelectedOption(FrameRateOption);
	}
}

void UGraphicsWidget::OnResolutionChanged(FString SelectedItem,ESelectInfo::Type SelectionType)
{
	if (!SettingsManager)
	{
		return;
	}

	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();

	if (!GameSettings)
	{
		return;
	}

	int32 Width = 0;
	int32 Height = 0;

	if (SelectedItem == TEXT("1280 x 720"))
	{
		Width = 1280;
		Height = 720;
	}
	else if (SelectedItem == TEXT("1600 x 900"))
	{
		Width = 1600;
		Height = 900;
	}
	else if (SelectedItem == TEXT("1920 x 1080"))
	{
		Width = 1920;
		Height = 1080;
	}
	else if (SelectedItem == TEXT("2560 x 1440"))
	{
		Width = 2560;
		Height = 1440;
	}
	else if (SelectedItem == TEXT("3840 x 2160"))
	{
		Width = 3840;
		Height = 2160;
	}

	if (Width > 0 && Height > 0)
	{
		SettingsManager->SetResolution(Width, Height);
	}
	GameSettings->ApplySettings(false);
}
void UGraphicsWidget::OnVSyncChanged(bool bIsChecked)
{
	if (!SettingsManager)
	{
		return;
	}

	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();

	if (!GameSettings)
	{
		return;
	}

	SettingsManager->SetVSyncEnabled(bIsChecked);
	GameSettings->ApplySettings(false);
}
void UGraphicsWidget::OnFrameRateChanged(FString SelectedItem,ESelectInfo::Type SelectionType)
{
	if (!SettingsManager)
	{
		return;
	}

	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();

	if (!GameSettings)
	{
		return;
	}

	float FrameRate = 60.0f;

	if (SelectedItem == TEXT("30 FPS"))
	{
		FrameRate = 30.0f;
	}
	else if (SelectedItem == TEXT("60 FPS"))
	{
		FrameRate = 60.0f;
	}
	else if (SelectedItem == TEXT("120 FPS"))
	{
		FrameRate = 120.0f;
	}
	else if (SelectedItem == TEXT("144 FPS"))
	{
		FrameRate = 144.0f;
	}
	else if (SelectedItem == TEXT("165 FPS"))
	{
		FrameRate = 165.0f;
	}
	else if (SelectedItem == TEXT("240 FPS"))
	{
		FrameRate = 240.0f;
	}
	else if (SelectedItem == TEXT("Unlimited"))
	{
		FrameRate = 0.0f;
	}

	SettingsManager->SetFrameRateLimit(FrameRate);
	GameSettings->ApplySettings(false);
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
