// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuCamera.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraTransitionFinished);

class UCameraComponent;
UCLASS()
class AMainMenuCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainMenuCamera();

	void MoveToTransform(FVector NewLocation, FRotator NewRotation);
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintAssignable) FOnCameraTransitionFinished OnCameraTransitionFinished;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector MainMenuLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator MainMenuRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector SettingsLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator SettingsRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector CreditsLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator CreditsRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector IdleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator IdleRotation;

private:
	FVector StartLocation;
	FVector TargetLocation;
	
	FRotator StartRotation;
	FRotator TargetRotation;
	
	float TransitionAlpha = 0.0f;
	
	bool bIsTransitioning = false;
	
	UPROPERTY(EditAnywhere, Category = "Camera Transition") float TransitionDuration = 0.7f;
};
