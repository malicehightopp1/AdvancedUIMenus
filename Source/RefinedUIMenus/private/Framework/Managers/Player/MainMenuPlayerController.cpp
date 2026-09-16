// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Managers/Player/MainMenuPlayerController.h"

#include "EnhancedInputComponent.h"
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
	
	//Controller Setup 
	
	if (GameMode->ControllerCursorWidgetClass)
	{
		ControllerCursorWidget = CreateWidget<UUserWidget>(this,GameMode->ControllerCursorWidgetClass);
	}
	if (ControllerCursorWidget)
	{
		//for top display
		ControllerCursorWidget->AddToViewport(100);
	}
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	ControllerCurorPOS = FVector2D(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
	
	ControllerCursorWidget->SetPositionInViewport(ControllerCurorPOS);
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

	EnhancedInput->BindAction(
		ControllerCurorAction,
		ETriggerEvent::Triggered,
		this,
		&AMainMenuPlayerController::MoveMenuCursor
	);
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

void AMainMenuPlayerController::MoveMenuCursor(const FInputActionValue& Value)
{
	FVector2D StickInput = Value.Get<FVector2D>();

	if (StickInput.IsNearlyZero())
	{
		return;
	}

	const float CursorSpeed = 800.0f;

	ControllerCurorPOS += StickInput * CursorSpeed * GetWorld()->GetDeltaSeconds();

	int32 ViewportSizeX;
	int32 ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	ControllerCurorPOS.X = FMath::Clamp(ControllerCurorPOS.X,0.0f,static_cast<float>(ViewportSizeX));

	ControllerCurorPOS.Y = FMath::Clamp(ControllerCurorPOS.Y,0.0f,static_cast<float>(ViewportSizeY));

	if (ControllerCursorWidget)
	{
		ControllerCursorWidget->SetPositionInViewport(ControllerCurorPOS);
	}
}
