// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsInternalWidgets/KeyRemappingWidgets/KeyRemappingWidget.h"

#include "KeyRemappingRowWidget.h"
#include "Components/VerticalBox.h"
#include "Framework/Managers/InputManagers/InputIconData.h"

void UKeyRemappingWidget::SetRemappingManager(UInputMappingManager* InRemappingManager)
{
	RemappingManager = InRemappingManager;
	
    BuildRemappingList();
}

void UKeyRemappingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RemappingManager)
	{
		BuildRemappingList();
	}
}

void UKeyRemappingWidget::BuildRemappingList()
{

    if (!RemappingList)
    {
        UE_LOG(LogTemp, Error,TEXT("RemappingList is NULL!"));
        return;
    }

    if (!KeyRemappingRowClass)
    {
        UE_LOG(LogTemp, Error,TEXT("RemappingRowClass is NULL!"));
        return;
    }

    if (!RemappingManager)
    {
        UE_LOG(LogTemp, Error,TEXT("RemappingManager is NULL!"));
        return;
    }

    RemappingList->ClearChildren();

    for (const FRemappableInput& Input : RemappableInputs)
    {

        if (Input.MappingName.IsNone())
        {
            UE_LOG(LogTemp, Warning,TEXT("Skipping mapping because MappingName is None."));
            continue;
        }

        UKeyRemappingRowWidget* Row =CreateWidget<UKeyRemappingRowWidget>(GetOwningPlayer(),KeyRemappingRowClass);

        if (!Row)
        {
            UE_LOG(LogTemp, Error,TEXT("FAILED to create row!"));
            continue;
        }

        Row->SetMappingName(Input.MappingName);
        Row->SetActionName(Input.DisplayName);
        Row->SetRemappingManager(RemappingManager);
        Row->SetInputIconData(InputIconData);

        RemappingList->AddChildToVerticalBox(Row);
    }
}
