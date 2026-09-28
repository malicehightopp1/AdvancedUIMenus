// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/WidgetComponents/AudioButtonBase.h"

#include "Kismet/GameplayStatics.h"

void UAudioButtonBase::OnButtonHovered()
{
	SetRenderScale(FVector2D(1.15f, 1.15f));
	SetBackgroundColor(FocusColor);
}

void UAudioButtonBase::OnButtonUnhovered()
{
	SetRenderScale(FVector2D(1.0f, 1.0f));
	SetBackgroundColor(NormalColor);
}

void UAudioButtonBase::OnButtonReceivedFocus()
{
	OnButtonHovered();
}

void UAudioButtonBase::OnButtonLostFocus()
{
	OnButtonUnhovered();
}

UAudioButtonBase::UAudioButtonBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
		
	OnClicked.AddUniqueDynamic(this, &UAudioButtonBase::PlayClickSound);
	OnHovered.AddUniqueDynamic(this, &UAudioButtonBase::OnButtonHovered);
	OnUnhovered.AddUniqueDynamic(this, &UAudioButtonBase::OnButtonUnhovered);
	
	OnReceivedFocus.BindUObject(this, &UAudioButtonBase::OnButtonReceivedFocus);
	OnLostFocus.BindUObject(this, &UAudioButtonBase::OnButtonLostFocus);
}

void UAudioButtonBase::SetControllerFocus(bool bIsFocused)
{
	if (bIsFocused)
	{
		OnButtonHovered();
	}
	else
	{
		OnButtonUnhovered();
	}
}

void UAudioButtonBase::PlayClickSound()
{
	if (!ClickSound)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(this, ClickSound);
}
