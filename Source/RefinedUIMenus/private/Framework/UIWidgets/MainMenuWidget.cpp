// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/MainMenuWidget.h"

#include "Components/TextBlock.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("MainMenuWidget::NativeConstruct()"));
	
	if (testTextBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Text set"));
		testTextBlock->SetText(FText::FromString(TEXT("Test Text"))); //set text
	}
}

bool UMainMenuWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Main menu widget has been init"))
	
	return true;
}

void UMainMenuWidget::InitWidgetData(const FString& InText)
{
	if (testTextBlock)
	{
		testTextBlock->SetText(FText::FromString(InText));
	}
}
