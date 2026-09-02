// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/SettingsWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"


void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("Settings Widget has been constructed"));
	
	if (TestingBlock)
	{
		TestingBlock->SetText(FText::FromString(TEXT("If this is Showing Everything is working!! :)")));
		TestingBlock->SetColorAndOpacity(FLinearColor::Red);
	}
}

bool USettingsWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	return true;
}

void USettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}
