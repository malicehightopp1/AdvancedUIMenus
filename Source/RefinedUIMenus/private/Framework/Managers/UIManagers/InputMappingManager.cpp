#include "InputMappingManager.h"

#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "InputCoreTypes.h"

void UInputMappingManager::Initialize(APlayerController* InPlayerController,UInputMappingContext* InPlayerMappingContext)
{
	PlayerController = InPlayerController;
	PlayerMappingContext = InPlayerMappingContext;

	if (!PlayerController)
	{
		return;
	}

	ULocalPlayer* LocalPlayer =PlayerController->GetLocalPlayer();

	if (!LocalPlayer)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!InputSubsystem)
	{
		return;
	}

	UserSettings = InputSubsystem->GetUserSettings();

	if (!UserSettings)
	{
		return;
	}

	if (PlayerMappingContext)
	{
		UserSettings->RegisterInputMappingContext(PlayerMappingContext);
	}
}

UEnhancedInputUserSettings* UInputMappingManager::GetUserSettings() const
{
	return UserSettings;
}

bool UInputMappingManager::GetCurrentKey(FName MappingName, FKey& OutKey) const
{
	OutKey = EKeys::Invalid;

	if (!UserSettings)
	{
		return false;
	}

	if (MappingName.IsNone())
	{
		return false;
	}

	const FPlayerKeyMapping* Mapping =UserSettings->FindCurrentMappingForSlot(MappingName,EPlayerMappableKeySlot::First);

	if (!Mapping)
	{
		return false;
	}

	OutKey = Mapping->GetCurrentKey();

	return OutKey.IsValid();
}

bool UInputMappingManager::GetDefaultKey(FName MappingName, FKey& OutKey) const
{
	OutKey = EKeys::Invalid;

	if (!UserSettings)
	{
		return false;
	}

	if (MappingName.IsNone())
	{
		return false;
	}

	const FPlayerKeyMapping* Mapping =UserSettings->FindCurrentMappingForSlot(MappingName,EPlayerMappableKeySlot::First);

	if (!Mapping)
	{
		return false;
	}

	OutKey = Mapping->GetDefaultKey();

	return OutKey.IsValid();
}

bool UInputMappingManager::RemapKey(FName MappingName, const FKey& NewKey, FText& OutFailureMessage)
{
	    OutFailureMessage = FText::GetEmpty();

    if (!UserSettings)
    {
        OutFailureMessage = FText::FromString(TEXT("Input settings are unavailable."));

        return false;
    }

    if (MappingName.IsNone())
    {
        OutFailureMessage = FText::FromString(TEXT("Invalid input mapping."));

        return false;
    }

    if (!NewKey.IsValid())
    {
        OutFailureMessage = FText::FromString(TEXT("Invalid key."));

        return false;
    }

    UEnhancedPlayerMappableKeyProfile* Profile = UserSettings->GetCurrentKeyProfile();

    if (!Profile)
    {
        OutFailureMessage =FText::FromString(TEXT("Input profile is unavailable."));

        return false;
    }
	

    FName ConflictingMapping;

    if (FindKeyConflict(MappingName,NewKey,ConflictingMapping))
    {
        OutFailureMessage = FText::Format(NSLOCTEXT("InputMapping","KeyConflict","That key is already assigned to {0}."),FText::FromName(ConflictingMapping));

        return false;
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
        OutFailureMessage = FText::FromString(TEXT("Unable to assign that key."));

        return false;
    }

	//marking the change
    bHasUnsavedChanges = true;

    return true;
}

bool UInputMappingManager::ResetMapping(FName MappingName)
{
	if (!UserSettings)
	{
		return false;
	}

	if (MappingName.IsNone())
	{
		return false;
	}

	FMapPlayerKeyArgs Args;

	Args.MappingName = MappingName;
	Args.Slot = EPlayerMappableKeySlot::First;

	FGameplayTagContainer FailureReason;

	UserSettings->ResetAllPlayerKeysInRow(Args,FailureReason);

	if (!FailureReason.IsEmpty())
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed to reset mapping: %s"),*MappingName.ToString());

		return false;
	}

	bHasUnsavedChanges = true;

	return true;
}

bool UInputMappingManager::ResetAllMappings()
{
	if (!UserSettings)
	{
		return false;
	}

	FGameplayTagContainer FailureReason;

	UserSettings->ResetKeyProfileIdToDefault(UserSettings->GetActiveKeyProfileId(),FailureReason);

	if (!FailureReason.IsEmpty())
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed to reset all input mappings."));

		return false;
	}

	bHasUnsavedChanges = true;

	return true;
}

bool UInputMappingManager::FindKeyConflict(FName MappingName, const FKey& Key, FName& OutConflictingMapping) const
{
	OutConflictingMapping = NAME_None;

	if (!UserSettings)
	{
		return false;
	}

	if (MappingName.IsNone())
	{
		return false;
	}

	if (!Key.IsValid())
	{
		return false;
	}

	UEnhancedPlayerMappableKeyProfile* Profile = UserSettings->GetCurrentKeyProfile();

	if (!Profile)
	{
		return false;
	}

	TArray<FName> MappingNamesUsingKey;

	Profile->GetMappingNamesForKey(Key,MappingNamesUsingKey);

	for (const FName ExistingMappingName : MappingNamesUsingKey)
	{
		if (ExistingMappingName != MappingName)
		{
			OutConflictingMapping =ExistingMappingName;

			return true;
		}
	}

	return false;
}

bool UInputMappingManager::ApplyMappings()
{
	if (!UserSettings)
	{
		return false;
	}

	UserSettings->ApplySettings();

	if (!SaveMappings())
	{
		return false;
	}

	bHasUnsavedChanges = false;

	return true;
}

bool UInputMappingManager::RevertMappings()
{
	if (!UserSettings)
	{
		return false;
	}

	if (!bHasUnsavedChanges)
	{
		return true;
	}

	if (!LoadMappings())
	{
		return false;
	}

	bHasUnsavedChanges = false;

	return true;
}

bool UInputMappingManager::SaveMappings()
{
	if (!UserSettings)
	{
		return false;
	}

	UserSettings->SaveSettings();

	return true;
}

bool UInputMappingManager::LoadMappings()
{
	if (!UserSettings)
	{
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Input mappings loaded from User Settings."));

	return true;
}

bool UInputMappingManager::HasUnsavedChanges() const
{
	return bHasUnsavedChanges;
}

void UInputMappingManager::ClearUnsavedChanges()
{
	bHasUnsavedChanges = false;
}
