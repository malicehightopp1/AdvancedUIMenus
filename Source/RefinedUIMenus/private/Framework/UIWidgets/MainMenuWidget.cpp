// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/MainMenuWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "Framework/Managers/InputManagers/InputDeviceManager.h"
#include "Framework/Services/ServiceLocatorSubsystem.h"
#include "WidgetComponents/AudioButtonBase.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
		
	SetIsFocusable(true);
	
	StartGameButton->IsFocusable = true;
	SettingsButton->IsFocusable = true;
	CreditsButton->IsFocusable = true;
	QuitButton->IsFocusable = true;
}

bool UMainMenuWidget::Initialize() //this is running but not the text block
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	return true;
}

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}
	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCreditsClicked);
	}
	
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);

	if (Services)
	{
		UInputDeviceManager* InputDeviceManager = Services->GetInputDeviceManager();

		if (InputDeviceManager)
		{
			InputDeviceManager->OnInputDeviceChanged.AddDynamic(this, &UMainMenuWidget::OnInputDeviceChanged);
		}
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	if (MainMenuManager)
	{
		MainMenuManager->StartGame();
	}
}

void UMainMenuWidget::OnSettingsClicked()
{
	if (MainMenuManager)
	{
		MainMenuManager->OpenSettings();
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit clicked, confirm quit should be open"))
	if (MainMenuManager)
	{
		MainMenuManager->OpenConfirmQuitMenu();
	}
}

void UMainMenuWidget::OnCreditsClicked()
{
	if (MainMenuManager)
	{
		MainMenuManager->OpenCredits();
	}
}

void UMainMenuWidget::SetMainMenuManager(UMainMenuManager* NewMainMenuManager)
{
	MainMenuManager = NewMainMenuManager;
}

void UMainMenuWidget::FocusStartButton()
{
	if (!StartGameButton)
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
		StartGameButton->SetKeyboardFocus();

		UE_LOG(LogTemp, Log, TEXT("General button focused because controller is being used"));
	}
}

void UMainMenuWidget::OnInputDeviceChanged(EInputDeviceType NewDeviceType)
{
	if (NewDeviceType == EInputDeviceType::Controller)
	{
		FocusStartButton();
	}
}
