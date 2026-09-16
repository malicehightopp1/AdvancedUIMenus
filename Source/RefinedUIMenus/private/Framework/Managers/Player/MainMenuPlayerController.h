// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

struct FInputActionValue;
class UUserWidget;
class UInputAction;

UCLASS()
class AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	void HandleAnyKey();
	
	//Controller Setup
	void MoveMenuCursor(const FInputActionValue& Value);
	
	UPROPERTY() UUserWidget* ControllerCursorWidget;
	
	FVector2D ControllerCurorPOS;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input") UInputAction* ControllerCurorAction;
};
