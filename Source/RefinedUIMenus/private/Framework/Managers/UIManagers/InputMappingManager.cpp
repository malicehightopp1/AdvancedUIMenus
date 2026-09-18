#include "InputMappingManager.h"

#include "Framework/UIWidgets/SettingsInternalWidgets/KeyRemappingWidgets/KeyRemappingRowWidget.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "InputCoreTypes.h"

void UInputMappingManager::Initialize(
    APlayerController* InPlayerController,
    UInputMappingContext* InPlayerMappingContext)
{
    PlayerController = InPlayerController;
    PlayerMappingContext = InPlayerMappingContext;

    if (!PlayerController)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("InputRemappingManager: PlayerController is null."));

        return;
    }

    ULocalPlayer* LocalPlayer =
        PlayerController->GetLocalPlayer();

    if (!LocalPlayer)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("InputRemappingManager: LocalPlayer is null."));

        return;
    }

    UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
        LocalPlayer->GetSubsystem<
            UEnhancedInputLocalPlayerSubsystem>();

    if (!InputSubsystem)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("InputRemappingManager: Input subsystem is null."));

        return;
    }

    UserSettings = InputSubsystem->GetUserSettings();

    if (!UserSettings)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("InputRemappingManager: User Settings are null."));

        return;
    }

    if (PlayerMappingContext)
    {
        UserSettings->RegisterInputMappingContext(
            PlayerMappingContext);
    }

    UE_LOG(
        LogTemp,
        Log,
        TEXT("Input Remapping Manager Initialized"));
}

UEnhancedInputUserSettings*
UInputMappingManager::GetUserSettings() const
{
    return UserSettings;
}

bool UInputMappingManager::GetCurrentKey(
    FName MappingName,
    FKey& OutKey) const
{
    if (!UserSettings || MappingName.IsNone())
    {
        return false;
    }

    const FPlayerKeyMapping* Mapping =
        UserSettings->FindCurrentMappingForSlot(
            MappingName,
            EPlayerMappableKeySlot::First);

    if (!Mapping)
    {
        return false;
    }

    OutKey = Mapping->GetCurrentKey();

    return OutKey.IsValid();
}

bool UInputMappingManager::RemapKey(
    FName MappingName,
    const FKey& NewKey,
    FText& OutFailureMessage)
{
    OutFailureMessage = FText::GetEmpty();

    if (!UserSettings)
    {
        OutFailureMessage =
            FText::FromString(
                TEXT("Input settings are unavailable."));

        return false;
    }

    if (MappingName.IsNone())
    {
        OutFailureMessage =
            FText::FromString(
                TEXT("Invalid input mapping."));

        return false;
    }

    if (!NewKey.IsValid())
    {
        OutFailureMessage =
            FText::FromString(
                TEXT("Invalid key."));

        return false;
    }

    UEnhancedPlayerMappableKeyProfile* Profile =
        UserSettings->GetCurrentKeyProfile();

    if (!Profile)
    {
        OutFailureMessage =
            FText::FromString(
                TEXT("Input profile is unavailable."));

        return false;
    }

    // Check whether another action already uses this key.
    TArray<FName> MappingNamesUsingKey;

    Profile->GetMappingNamesForKey(
        NewKey,
        MappingNamesUsingKey);

    for (const FName ExistingMappingName :
         MappingNamesUsingKey)
    {
        if (ExistingMappingName != MappingName)
        {
            OutFailureMessage =
                FText::FromString(
                    TEXT("That key is already in use."));

            return false;
        }
    }

    FMapPlayerKeyArgs Args;

    Args.MappingName = MappingName;
    Args.Slot = EPlayerMappableKeySlot::First;
    Args.NewKey = NewKey;
    Args.bCreateMatchingSlotIfNeeded = false;

    FGameplayTagContainer FailureReason;

    UserSettings->MapPlayerKey(
        Args,
        FailureReason);

    if (!FailureReason.IsEmpty())
    {
        OutFailureMessage =
            FText::FromString(
                TEXT("Unable to assign that key."));

        return false;
    }

    UserSettings->ApplySettings();

    SaveMappings();

    UE_LOG(
        LogTemp,
        Log,
        TEXT("Input mapping changed: %s -> %s"),
        *MappingName.ToString(),
        *NewKey.ToString());

    return true;
}

void UInputMappingManager::ResetMapping(
    FName MappingName)
{
    if (!UserSettings || MappingName.IsNone())
    {
        return;
    }

    FMapPlayerKeyArgs Args;

    Args.MappingName = MappingName;
    Args.Slot = EPlayerMappableKeySlot::First;

    FGameplayTagContainer FailureReason;

    UserSettings->ResetAllPlayerKeysInRow(
        Args,
        FailureReason);

    UserSettings->ApplySettings();

    SaveMappings();
}

void UInputMappingManager::ResetAllMappings()
{
    if (!UserSettings)
    {
        return;
    }

    FGameplayTagContainer FailureReason;

    UserSettings->ResetKeyProfileIdToDefault(
        UserSettings->GetActiveKeyProfileId(),
        FailureReason);

    UserSettings->ApplySettings();

    SaveMappings();
}

void UInputMappingManager::SaveMappings()
{
    if (!UserSettings)
    {
        return;
    }

    UserSettings->SaveSettings();
}