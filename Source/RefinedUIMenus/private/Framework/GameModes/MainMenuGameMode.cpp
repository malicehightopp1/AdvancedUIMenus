// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GameModes/MainMenuGameMode.h"
#include "Framework/Managers/Player/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	
	DefaultPawnClass = nullptr;
}
