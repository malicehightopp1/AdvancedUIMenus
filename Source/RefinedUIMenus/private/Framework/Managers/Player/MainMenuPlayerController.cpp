// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/Player/MainMenuPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Framework/GameModes/MainMenuGameMode.h"
#include "Framework/Services/ServiceLocatorSubsystem.h"
#include "Framework/Managers/UIManagers/MainMenuManager.h"
#include "InputCoreTypes.h"
#include "AI/NavigationSystemBase.h"
#include "Framework/Managers/SavingManager/SettingsSaveManager.h"
#include "Framework/Managers/UIManagers/SettingsManager.h"
#include "Framework/UIWidgets/CreditsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCamera/MainMenuCamera.h"
#include "Framework/Application/SlateApplication.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AMainMenuCamera* MainMenuCamera = Cast<AMainMenuCamera>(UGameplayStatics::GetActorOfClass(GetWorld(),AMainMenuCamera::StaticClass()));

	if (!MainMenuCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("Main Menu Camera was not found!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Main Menu Camera found: %s"), *MainMenuCamera->GetName());
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);

	if (!Services)
	{
		return;
	}

	AMainMenuGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainMenuGameMode>();

	if (!GameMode)
	{
		return;
	}

	UMainMenuManager* MenuManager = Services->GetMainMenuManager();

	if (!MenuManager)
	{
		return;
	}

	USettingsManager* SettingsManager = Services->GetSettingsManager();
	
	MenuManager->Initialize( this, GameMode->MainMenuWidgetClass, GameMode->SettingsWidgetClass, MainMenuCamera, GameMode->MainMenuMusic, GameMode->CreditsWidgetClass, GameMode->ConfirmWidgetClass);
	
	if (!SettingsManager)
	{
		return;
	}
	
	SettingsManager->Initialize(this,GameMode->SettingsWidgetClass,GameMode->MasterSoundClass,GameMode->MusicSoundClass,GameMode->SFXSoundClass,GameMode->SettingsSoundMix);
	
	USettingsSaveManager* SettingsSaveManager = Services->GetSettingsSaveManager();
	
	if (!SettingsSaveManager)
	{
		return;
	}
	
	SettingsSaveManager->Initialize(SettingsManager);
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (ControllerMappingContext)
			{
				InputSubsystem->AddMappingContext(ControllerMappingContext, 0);
			}
		}
	}
}

void AMainMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &AMainMenuPlayerController::HandleAnyKey);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	
	if (!EnhancedInput)
	{
		return;
	}

	EnhancedInput->BindAction(ControllerCurorAction, ETriggerEvent::Triggered, this, &AMainMenuPlayerController::TestNav);
	EnhancedInput->BindAction(ControllerAcceptAction, ETriggerEvent::Started, this, &AMainMenuPlayerController::AccpetMenuCursor);
}

//for begin idle state
void AMainMenuPlayerController::HandleAnyKey()
{
	UServiceLocatorSubSystem* Services = UServiceLocatorSubSystem::Get(this);
	if (!Services)
	{
		return;
	}
	UMainMenuManager* MenuManager = Services->GetMainMenuManager();
	if (MenuManager)
	{
		MenuManager->PressAnyKey();
	}
}

void AMainMenuPlayerController::AccpetMenuCursor(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("A key pressed"));
}

void AMainMenuPlayerController::TestNav(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	if (Input.IsNearlyZero())
	{
		return;
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("MENU NAVIGATION: X=%f Y=%f"),
		Input.X,
		Input.Y
	);
}
