// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/WidgetComponents/ConfirmQuit.h"

#include "AudioButtonBase.h"
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
	if (QuitButtonYes)
	{
		QuitButtonYes->SetKeyboardFocus();
	}
}

void UConfirmQuit::SetMainMenuManager(UMainMenuManager* NewMainMenuManager)
{
	MainMenuManager = NewMainMenuManager;
}
