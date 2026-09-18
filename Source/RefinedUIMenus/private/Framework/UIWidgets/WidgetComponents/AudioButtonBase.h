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
	
	UAudioButtonBase(const FObjectInitializer& ObjectInitializer);
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")USoundBase* ClickSound;

	UFUNCTION()void SetControllerFocus(bool bIsFocused);
protected:
	virtual void PostLoad() override;

	virtual void PostInitProperties() override;
	
	UFUNCTION()void OnButtonHovered();

	UFUNCTION()void OnButtonUnhovered();
	
	UFUNCTION() void OnButtonReceivedFocus();
	UFUNCTION() void OnButtonLostFocus();
	
private:

	UFUNCTION()void PlayClickSound();
	
	UPROPERTY(EditAnywhere, Category = "Color") FLinearColor NormalColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, Category = "Color") FLinearColor FocusColor = FLinearColor::Gray;
};
