// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UWidget;
class UInputMappingContext;
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
	void AccpetMenuCursor(const FInputActionValue& Value);
	void TestNav(const FInputActionValue& Value);


	UPROPERTY(EditAnywhere, Category = "Input") UInputMappingContext* RemappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input") UInputMappingContext* ControllerMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input") UInputAction* ControllerCurorAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input") UInputAction* ControllerAcceptAction;

};
