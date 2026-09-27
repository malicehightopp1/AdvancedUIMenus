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

    // =========================================================
    // Initialization
    // =========================================================

    void Initialize(APlayerController* InPlayerController,UInputMappingContext* InPlayerMappingContext);

    // =========================================================
    // User Settings
    // =========================================================

    UEnhancedInputUserSettings* GetUserSettings() const;

    // =========================================================
    // Current Keys
    // =========================================================

    bool GetCurrentKey(FName MappingName,FKey& OutKey) const;

    bool GetDefaultKey(FName MappingName,FKey& OutKey) const;

    // =========================================================
    // Remapping
    // =========================================================

    bool RemapKey(FName MappingName,const FKey& NewKey,FText& OutFailureMessage);

    // =========================================================
    // Reset
    // =========================================================

    bool ResetMapping(FName MappingName);

    bool ResetAllMappings();

    // =========================================================
    // Conflict Detection
    // =========================================================

    bool FindKeyConflict(FName MappingName,const FKey& Key,FName& OutConflictingMapping) const;

    // =========================================================
    // Apply / Revert
    // =========================================================

    bool ApplyMappings();

    bool RevertMappings();

    // =========================================================
    // Save / Load
    // =========================================================

    bool SaveMappings();

    bool LoadMappings();

    // =========================================================
    // Unsaved Changes
    // =========================================================

    bool HasUnsavedChanges() const;

    void ClearUnsavedChanges();

private:

    // =========================================================
    // References
    // =========================================================

    UPROPERTY()
    TObjectPtr<APlayerController> PlayerController;

    UPROPERTY()
    TObjectPtr<UInputMappingContext> PlayerMappingContext;

    UPROPERTY()
    TObjectPtr<UEnhancedInputUserSettings> UserSettings;

    // =========================================================
    // State
    // =========================================================

    bool bHasUnsavedChanges = false;
};
