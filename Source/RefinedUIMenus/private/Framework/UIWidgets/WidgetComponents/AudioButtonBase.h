// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "AudioButtonBase.generated.h"


class USoundBase;

UCLASS()
class UAudioButtonBase : public UButton
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")USoundBase* ClickSound;

protected:

	virtual void PostLoad() override;

	virtual void PostInitProperties() override;

private:

	UFUNCTION()void PlayClickSound();
};
