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
}

void UAudioButtonBase::PlayClickSound()
{
	if (!ClickSound)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(this, ClickSound);
}
