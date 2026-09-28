// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/WidgetComponents/ConfirmQuit.h"
#include "AudioButtonBase.h"
#include "Framework/Managers/InputManagers/InputDeviceManager.h"
#include "Framework/Services/ServiceLocatorSubsystem.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"

void UConfirmQuit::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (QuitButtonYes)
	{
		QuitButtonYes->OnClicked.AddDynamic(this, &UConfirmQuit::OnYesClicked);
		QuitButtonYes->IsFocusable = true;
	}
	if (QuitButtonNo)
	{
		QuitButtonNo->OnClicked.AddDynamic(this, &UConfirmQuit::OnNoClicked);
		QuitButtonNo->IsFocusable = true;
	}
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);

	if (Services)
	{
		UInputDeviceManager* InputDeviceManager = Services->GetInputDeviceManager();

		if (InputDeviceManager)
		{
			InputDeviceManager->OnInputDeviceChanged.AddDynamic(this, &UConfirmQuit::OnInputDeviceChanged);
		}
	}
}

void UConfirmQuit::OnInputDeviceChanged(EInputDeviceType NewDeviceType)
{
	if (NewDeviceType == EInputDeviceType::Controller)
	{
		FocusYesButton();
	}
}

void UConfirmQuit::OnYesClicked()
{
	if (MainMenuManager)
	{
		MainMenuManager->QuitGame();
	}
}

void UConfirmQuit::OnNoClicked()
{
	if (MainMenuManager)
	{
		MainMenuManager->CloseConfirmQuitMenu();
	}
}

void UConfirmQuit::FocusYesButton()
{
	if (!QuitButtonYes)
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
		QuitButtonYes->SetKeyboardFocus();

		UE_LOG(LogTemp, Log, TEXT("General button focused because controller is being used"));
	}
}

void UConfirmQuit::SetMainMenuManager(UMainMenuManager* NewMainMenuManager)
{
	MainMenuManager = NewMainMenuManager;
}
