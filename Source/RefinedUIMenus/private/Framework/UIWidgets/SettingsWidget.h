// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

class USettingsManager;
class UTextBlock;
class UCanvasPanel;
class UOverlay;
class UBorder;
class UButton;
class UWidgetSwitcher;
class UMainMenuManager;
class UGraphicsWidget;
class UAudioWidget;
class UControlsWidget;
class UGeneralWidget;

UCLASS()
class USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeOnInitialized() override;
	
	UFUNCTION() void SetSettingsManager(USettingsManager* NewSettingsManager);

	
	UFUNCTION() void OnBackButtonPressed();
	
	UFUNCTION() void OnGeneralClicked();
	UFUNCTION() void OnGraphicsClicked();
	UFUNCTION() void OnAudioClicked();
	UFUNCTION() void OnControlsClicked();
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UWidgetSwitcher> PanelSwitcher;  //settings manager is using this
private:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UOverlay> ComponentHoldersOverlay;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UBorder> SettingsBackground;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> BackButton;
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> GeneralButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> GraphicsButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> AudioButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> ControlsButton;
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UGraphicsWidget> GraphicsWidget;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UControlsWidget> ControlsWidget;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UAudioWidget> AudioWidget;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UGeneralWidget> GeneralWidget ;

	UPROPERTY() TObjectPtr<USettingsManager> SettingsManager; 
};
