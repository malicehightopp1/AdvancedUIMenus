// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/MainMenuWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (TestTextBlock)
	{
		TestTextBlock->SetText(FText::FromString(TEXT("TestTextBlock")));
	}
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

}

