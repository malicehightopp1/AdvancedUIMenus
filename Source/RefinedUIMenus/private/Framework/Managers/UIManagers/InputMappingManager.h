// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputMappingManager.generated.h"

class UEnhancedInputUserSettings;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class UInputMappingManager : public UObject
{
	GENERATED_BODY()
public:

	void Initialize(APlayerController* InPlayerController,UInputMappingContext* InPlayerMappingContext);

	UEnhancedInputUserSettings* GetUserSettings() const;

	bool GetCurrentKey(
		FName MappingName,
		FKey& OutKey) const;

	bool RemapKey(
		FName MappingName,
		const FKey& NewKey,
		FText& OutFailureMessage);

	void ResetMapping(FName MappingName);

	void ResetAllMappings();

	void SaveMappings();

private:

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY()
	TObjectPtr<UEnhancedInputUserSettings> UserSettings;
};
