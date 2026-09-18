#include "KeyRemappingRowWidget.h"

#include "Framework/UIWidgets/SettingsInternalWidgets/KeyRemappingWidgets/KeyRemappingRowWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "InputAction.h"
#include "Framework/Managers/UIManagers/InputMappingManager.h"

void UKeyRemappingRowWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetIsFocusable(true);

    if (ChangeButton)
    {
        ChangeButton->OnClicked.AddUniqueDynamic(
            this,
            &UKeyRemappingRowWidget::OnChangeButtonClicked);
    }

    RefreshCurrentKey();

    if (StatusText)
    {
        StatusText->SetText(FText::GetEmpty());
    }
}

void UKeyRemappingRowWidget::SetInputAction(UInputAction* InInputAction)
{
    InputAction = InInputAction;
}

void UKeyRemappingRowWidget::SetActionName(const FText& InName)
{
    if (ActionNameText)
    {
        ActionNameText->SetText(InName);
    }
}

void UKeyRemappingRowWidget::SetMappingName(FName InMappingName)
{
    MappingName = InMappingName;

    RefreshCurrentKey();
}

void UKeyRemappingRowWidget::SetRemappingManager(UInputMappingManager* InRemappingManager)
{
    RemappingManager = InRemappingManager;

    RefreshCurrentKey();
}

void UKeyRemappingRowWidget::RefreshCurrentKey()
{
    if (!CurrentKeyText || !RemappingManager || MappingName.IsNone())
    {
        return;
    }

    FKey CurrentKey;

    if (RemappingManager->GetCurrentKey(MappingName, CurrentKey))
    {
        CurrentKeyText->SetText(
            CurrentKey.GetDisplayName(false));
    }
}

void UKeyRemappingRowWidget::OnChangeButtonClicked()
{
    BeginKeyRemap();
}

void UKeyRemappingRowWidget::BeginKeyRemap()
{
    bWaitingForKey = true;

    if (StatusText)
    {
        StatusText->SetText(
            FText::FromString(TEXT("Press a key...")));
    }

    SetKeyboardFocus();
}

void UKeyRemappingRowWidget::CancelKeyRemap()
{
    bWaitingForKey = false;

    if (StatusText)
    {
        StatusText->SetText(FText::GetEmpty());
    }
}

void UKeyRemappingRowWidget::ApplyNewKey(const FKey& NewKey)
{
    if (!RemappingManager || MappingName.IsNone())
    {
        CancelKeyRemap();
        return;
    }

    FText FailureMessage;

    const bool bSuccess =
        RemappingManager->RemapKey(
            MappingName,
            NewKey,
            FailureMessage);

    if (bSuccess)
    {
        bWaitingForKey = false;

        if (StatusText)
        {
            StatusText->SetText(FText::GetEmpty());
        }

        RefreshCurrentKey();
    }
    else
    {
        if (StatusText)
        {
            StatusText->SetText(FailureMessage);
        }

        bWaitingForKey = false;
    }
}

FReply UKeyRemappingRowWidget::NativeOnPreviewKeyDown(
    const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    if (!bWaitingForKey)
    {
        return Super::NativeOnPreviewKeyDown(
            InGeometry,
            InKeyEvent);
    }

    const FKey PressedKey = InKeyEvent.GetKey();

    if (PressedKey == EKeys::Escape)
    {
        CancelKeyRemap();

        return FReply::Handled();
    }

    if (!PressedKey.IsValid())
    {
        return FReply::Handled();
    }

    ApplyNewKey(PressedKey);

    return FReply::Handled();
}

FReply UKeyRemappingRowWidget::NativeOnPreviewMouseButtonDown(
    const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    if (!bWaitingForKey)
    {
        return Super::NativeOnPreviewMouseButtonDown(
            InGeometry,
            InMouseEvent);
    }

    const FKey MouseKey = InMouseEvent.GetEffectingButton();

    if (!MouseKey.IsValid())
    {
        return FReply::Handled();
    }

    ApplyNewKey(MouseKey);

    return FReply::Handled();
}