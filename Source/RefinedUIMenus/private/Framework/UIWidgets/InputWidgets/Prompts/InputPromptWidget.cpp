 // Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/InputWidgets/Prompts/InputPromptWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Framework/Managers/InputManagers/InputDeviceManager.h"
#include "Framework/Services/ServiceLocatorSubSystem.h"

void UInputPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UServiceLocatorSubSystem* ServiceLocatorSubSystem = UServiceLocatorSubSystem::Get(this);
	if (!ServiceLocatorSubSystem)
	{
		return;
	}
	InputDeviceManager = ServiceLocatorSubSystem->GetInputDeviceManager();
	
	if (!InputDeviceManager)
	{
		return;
	}
	
	InputDeviceManager->OnInputDeviceChanged.AddUObject(this, &UInputPromptWidget::InputDeviceChanged);
	
	CurrentDevice = InputDeviceManager->IsUsingController() ? EInputPromptDevice::Controller : EInputPromptDevice::Keyboard;
	
	RefreshPrompts();
}

void UInputPromptWidget::SetInputDevice(EInputPromptDevice NewDevice)
{
	if (CurrentDevice == NewDevice)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Setting input device %hhd"), NewDevice);
	CurrentDevice = NewDevice;

	RefreshPrompts();
}

void UInputPromptWidget::SetBackPrompt(const FText& InText)
{
	BackPromptText = InText;

	if (BackText)
	{
		BackText->SetText(BackPromptText);
	}
}

void UInputPromptWidget::SetAcceptPrompt(const FText& InText)
{
	AcceptPromptText = InText;

	if (AcceptText)
	{
		AcceptText->SetText(AcceptPromptText);
	}
}

void UInputPromptWidget::RefreshPrompts()
{
	const bool bUsingController = CurrentDevice == EInputPromptDevice::Controller;

	if (BackKeyboardIcon)
	{
		BackKeyboardIcon->SetVisibility(bUsingController? ESlateVisibility::Collapsed: ESlateVisibility::Visible);
	}

	if (BackControllerIcon)
	{
		BackControllerIcon->SetVisibility(bUsingController? ESlateVisibility::Visible: ESlateVisibility::Collapsed);
	}

	if (AcceptKeyboardIcon)
	{
		AcceptKeyboardIcon->SetVisibility(bUsingController? ESlateVisibility::Collapsed: ESlateVisibility::Visible);
	}

	if (AcceptControllerIcon)
	{
		AcceptControllerIcon->SetVisibility(bUsingController? ESlateVisibility::Visible: ESlateVisibility::Collapsed);
	}

	if (BackText)
	{
		BackText->SetText(BackPromptText);
	}

	if (AcceptText)
	{
		AcceptText->SetText(AcceptPromptText);
	}
}

 void UInputPromptWidget::InputDeviceChanged(EInputDeviceType NewInputDevice)
 {
	if (NewInputDevice == EInputDeviceType::Controller)
	{
		SetInputDevice(EInputPromptDevice::Controller);
	}
	else
	{
		SetInputDevice(EInputPromptDevice::Keyboard);
	}
 }
