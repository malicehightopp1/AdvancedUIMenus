// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/MainMenuWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("MainMenuWidget::NativeConstruct()"));
	
	CanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	TestTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	if (TestTextBlock) //text block is null
	{
		UE_LOG(LogTemp, Warning, TEXT("Text set"));
		TestTextBlock->SetText(FText::FromString(TEXT("Test Text"))); //set text
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Text"));
	}
	
}

bool UMainMenuWidget::Initialize() //this is running but not the text block
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Main menu widget has been init"))
	
	return true;
}
