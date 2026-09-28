// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Managers/InputManagers/InputDeviceManager.h"
#include "InputPromptWidget.generated.h"

class UInputDeviceManager;
class UTextBlock;
class UImage;

UENUM(BlueprintType)
enum class EInputPromptDevice : uint8
{
	Keyboard,
	Controller
};
UCLASS()
class UInputPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetInputDevice(EInputPromptDevice NewDevice);

	void SetBackPrompt(const FText& InText);
	void SetAcceptPrompt(const FText& InText);

protected:

	virtual void NativeConstruct() override;

	void RefreshPrompts();

protected:

	UPROPERTY(meta = (BindWidget))TObjectPtr<UImage> BackKeyboardIcon;
	UPROPERTY(meta = (BindWidget))TObjectPtr<UImage> BackControllerIcon;
	UPROPERTY(meta = (BindWidget))TObjectPtr<UTextBlock> BackText;
	UPROPERTY(meta = (BindWidget))TObjectPtr<UImage> AcceptKeyboardIcon;
	UPROPERTY(meta = (BindWidget))TObjectPtr<UImage> AcceptControllerIcon;
	UPROPERTY(meta = (BindWidget))TObjectPtr<UTextBlock> AcceptText;

private:

	UPROPERTY() UInputDeviceManager* InputDeviceManager = nullptr;
	
	UFUNCTION() void InputDeviceChanged(EInputDeviceType NewInputDevice);
	
	EInputPromptDevice CurrentDevice = EInputPromptDevice::Keyboard;

	FText BackPromptText = FText::FromString(TEXT("Back"));
	FText AcceptPromptText = FText::FromString(TEXT("Select"));
};
