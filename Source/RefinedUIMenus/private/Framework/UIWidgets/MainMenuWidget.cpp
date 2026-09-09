// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/MainMenuWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
		
	SetIsFocusable(true);
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
	if (MainMenuManager)
	{
		MainMenuManager->QuitGame();
	}
}

void UMainMenuWidget::SetMainMenuManager(UMainMenuManager* NewMainMenuManager)
{
	MainMenuManager = NewMainMenuManager;
}
