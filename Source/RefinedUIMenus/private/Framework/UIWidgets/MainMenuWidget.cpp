// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/MainMenuWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//Dont put construction data here it wont work, bad for performance put all construction in init. 
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

	ConstructWidget();
}

void UMainMenuWidget::ConstructWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget construct function has been called"));
	
	CanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	WidgetTree->RootWidget = CanvasPanel;
	
	TestTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	TestTextBlock->SetText(FText::FromString(TEXT("The text is working all through C++ ;)")));
	TestTextBlock->SetJustification(ETextJustify::Center);
	
	//Setting anchors in canvas panel for specific objects 
	UCanvasPanelSlot* slot = CanvasPanel->AddChildToCanvas(TestTextBlock);
	slot->SetAnchors(FAnchors(0.5f, 0.5f));
	
}
