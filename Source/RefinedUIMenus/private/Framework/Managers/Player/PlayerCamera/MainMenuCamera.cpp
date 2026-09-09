// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Managers/Player/PlayerCamera/MainMenuCamera.h"


AMainMenuCamera::AMainMenuCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainMenuCamera::MoveToTransform(FVector NewLocation, FRotator NewRotation)
{
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	
	TargetLocation = NewLocation;
	TargetRotation = NewRotation;
	
	TransitionAlpha = 0.0f;
	
	bIsTransitioning = true;
	
	UE_LOG(LogTemp,Log,TEXT("Transition started"));
}

void AMainMenuCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsTransitioning)
	{
		return;
	}
	TransitionAlpha += DeltaTime / TransitionDuration;
	
	float Alpha = FMath::Clamp(TransitionAlpha, 0.0f, 1.0f);
	
	Alpha = FMath::InterpEaseInOut(0.0f, 1.0f, Alpha, 2.0f);
	
	FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);
	
	FRotator NewRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
	
	SetActorLocation(NewLocation);
	SetActorRotation(NewRotation);
	
	if (TransitionAlpha >= 1.0f)
	{
		SetActorLocation(TargetLocation);
		SetActorRotation(TargetRotation);
		
		bIsTransitioning = false;
		
		UE_LOG(LogTemp,Log,TEXT("Transition finished"));
		
		OnCameraTransitionFinished.Broadcast();
	}
}
