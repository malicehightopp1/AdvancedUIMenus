// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/CreditsWidget.h"

#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "WidgetComponents/AudioButtonBase.h"

void UCreditsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UCreditsWidget::OnBackButtonPressed);
		BackButton->IsFocusable = true;
	}
}

void UCreditsWidget::FocusBackButton()
{
	if (BackButton)
	{
		BackButton->SetKeyboardFocus();
	}
}

void UCreditsWidget::SetMainMenuManager(UMainMenuManager* InMainMenuManager)
{
	MainMenuManager = InMainMenuManager;
}

void UCreditsWidget::OnBackButtonPressed()
{
	if (MainMenuManager)
	{
		MainMenuManager->GoBack();
	}
}
