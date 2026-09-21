// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/ControlsWidget.h"

#include "KeyRemappingWidgets/KeyRemappingWidget.h"

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

