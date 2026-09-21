// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputDeviceManager.generated.h"

UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	KeyboardMouse,
	Controller
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChanged, EInputDeviceType);

UCLASS()
class UInputDeviceManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();
	
	void ProcessInputDevice(const FKey& Key);
	
	EInputDeviceType GetInputDeviceType() const
	{
		return CurrentInputDevice;
	}
	bool IsUsingController() const
	{
		return CurrentInputDevice == EInputDeviceType::Controller;
	}
	bool IsUsingKeyboard() const
	{
		return CurrentInputDevice == EInputDeviceType::KeyboardMouse;
	}
	
	FOnInputDeviceChanged OnInputDeviceChanged;
	
private:
	EInputDeviceType CurrentInputDevice = EInputDeviceType::KeyboardMouse;
};
