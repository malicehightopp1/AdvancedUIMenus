// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/InputManagers/InputDeviceManager.h"

void UInputDeviceManager::Initialize()
{
	CurrentInputDevice = EInputDeviceType::KeyboardMouse;
	UE_LOG(LogTemp, Warning, TEXT("UInputDeviceManager::Initialize"))
}

void UInputDeviceManager::ProcessInputDevice(const FKey& Key)
{
	if (!Key.IsValid())
	{
		return;
	}
	EInputDeviceType NewDevice;

	if (Key.IsGamepadKey())
	{
		NewDevice = EInputDeviceType::Controller;
		UE_LOG(LogTemp, Warning, TEXT("Device is Controller"))
	}
	else
	{
		NewDevice = EInputDeviceType::KeyboardMouse;
		UE_LOG(LogTemp, Warning, TEXT("Device is KeyBoard"))
	}

	if (NewDevice == CurrentInputDevice)
	{
		return;
	}

	CurrentInputDevice = NewDevice;

	OnInputDeviceChanged.Broadcast(NewDevice);
}

