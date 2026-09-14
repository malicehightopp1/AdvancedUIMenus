// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmQuit.generated.h"

class UMainMenuManager;
class UAudioButtonBase;

UCLASS()
class UConfirmQuit : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioButtonBase> QuitButtonNo;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioButtonBase> QuitButtonYes;
	
	UFUNCTION() void OnYesClicked();
	UFUNCTION() void OnNoClicked();
	
	UFUNCTION() void SetMainMenuManager(UMainMenuManager* NewMainMenuManager);
	
	UPROPERTY()TObjectPtr<UMainMenuManager> MainMenuManager;;
};
