// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/ControlsWidget.h"

#include "Components/TextBlock.h"
#include "Framework/Managers/UIManagers/InputMappingManager.h"
#include "Framework/UIWidgets/WidgetComponents/AudioButtonBase.h"
#include "KeyRemappingWidgets/KeyRemappingWidget.h"

void UControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (SaveButton)
	{
		SaveButton->OnClicked.AddUniqueDynamic(this, &UControlsWidget::OnSavedclicked);
	}
	if (DontSaveButton)
	{
		DontSaveButton->OnClicked.AddUniqueDynamic(this, &UControlsWidget::OnDontSaveclicked);
	}
	if (ResetAllButton)
	{
		ResetAllButton->OnClicked.AddUniqueDynamic(this, &UControlsWidget::OnResetAllClicked);
	}
	
	RefreshUnsavedState();
}

void UControlsWidget::SetInputMappingManager(UInputMappingManager* InInputMappingManager)
{
	InputMappingManager = InInputMappingManager;
	
	UE_LOG(LogTemp, Warning, TEXT("UControlsWidget::function called"));
	if (KeyRemappingWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UControlsWidget::Set input mapping manager"));
		KeyRemappingWidget->SetRemappingManager(InputMappingManager);
	}
}

void UControlsWidget::OnSavedclicked()
{
	if (!InputMappingManager)
	{
		return;
	}

	if (InputMappingManager->ApplyMappings())
	{
		RefreshUnsavedState();
	}
}

void UControlsWidget::OnDontSaveclicked()
{
	if (!InputMappingManager)
	{
		return;
	}

	if (InputMappingManager->RevertMappings())
	{
		KeyRemappingWidget->BuildRemappingList();
		RefreshUnsavedState();
	}
}

void UControlsWidget::OnResetAllClicked()
{
	if (!InputMappingManager)
	{
		return;
	}

	if (InputMappingManager->ResetAllMappings())
	{
		KeyRemappingWidget->BuildRemappingList();
		RefreshUnsavedState();
	}
}

void UControlsWidget::RefreshUnsavedState()
{
	if (!InputMappingManager || !UnSavedChanges)
	{
		return;
	}

	if (InputMappingManager->HasUnsavedChanges())
	{
		UnSavedChanges->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UnSavedChanges->SetVisibility(ESlateVisibility::Collapsed);
	}
}

