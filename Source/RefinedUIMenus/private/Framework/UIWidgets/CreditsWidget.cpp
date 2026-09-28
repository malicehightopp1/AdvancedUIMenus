// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/CreditsWidget.h"

#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "Framework/Managers/InputManagers/InputDeviceManager.h"
#include "Framework/Services/ServiceLocatorSubsystem.h"
#include "WidgetComponents/AudioButtonBase.h"

void UCreditsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UCreditsWidget::OnBackButtonPressed);
		BackButton->IsFocusable = true;
	}
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);

	if (Services)
	{
		UInputDeviceManager* InputDeviceManager = Services->GetInputDeviceManager();

		if (InputDeviceManager)
		{
			InputDeviceManager->OnInputDeviceChanged.AddDynamic(this, &UCreditsWidget::OnInputDeviceChanged);
		}
	}
}

void UCreditsWidget::FocusBackButton()
{
	if (!BackButton)
	{
		return;
	}

	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);

	if (!Services)
	{
		return;
	}

	UInputDeviceManager* InputDeviceManager = Services->GetInputDeviceManager();

	if (!InputDeviceManager)
	{
		return;
	}

	if (InputDeviceManager->IsUsingController())
	{
		BackButton->SetKeyboardFocus();

		UE_LOG(LogTemp, Log, TEXT("General button focused because controller is being used"));
	}
}

void UCreditsWidget::OnInputDeviceChanged(EInputDeviceType NewDeviceType)
{
	if (NewDeviceType == EInputDeviceType::Controller)
	{
		FocusBackButton();
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
