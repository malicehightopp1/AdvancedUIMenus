// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UIWidgets/WidgetComponents/AudioButtonBase.h"

#include "Kismet/GameplayStatics.h"

void UAudioButtonBase::PostLoad()
{
	Super::PostLoad();
	
	OnClicked.AddUniqueDynamic(this, &UAudioButtonBase::PlayClickSound);
}

void UAudioButtonBase::PostInitProperties()
{
	Super::PostInitProperties();
	
	OnClicked.AddUniqueDynamic(this, &UAudioButtonBase::PlayClickSound);
	OnHovered.AddDynamic(this, &UAudioButtonBase::OnButtonHovered);
	OnUnhovered.AddDynamic(this, &UAudioButtonBase::OnButtonUnhovered);
}

void UAudioButtonBase::OnButtonHovered()
{
	SetRenderScale(FVector2D(1.05f, 1.05f));
}

void UAudioButtonBase::OnButtonUnhovered()
{
	SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UAudioButtonBase::PlayClickSound()
{
	if (!ClickSound)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(this, ClickSound);
}
