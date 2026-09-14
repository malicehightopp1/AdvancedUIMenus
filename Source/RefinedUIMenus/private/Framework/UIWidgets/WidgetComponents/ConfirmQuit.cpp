// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/WidgetComponents/ConfirmQuit.h"

#include "Framework/Managers/UIManagers/MainMenuManager.h"

void UConfirmQuit::OnYesClicked()
{
	if (MainMenuManager)
	{
		MainMenuManager->QuitGame();
	}
}

void UConfirmQuit::OnNoClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UConfirmQuit::SetMainMenuManager(UMainMenuManager* NewMainMenuManager)
{
	MainMenuManager = NewMainMenuManager;
}
