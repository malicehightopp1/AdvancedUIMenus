// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UWidgetSwitcher;
class USizeBox;
class UVerticalBox;
class UBorder;
class UOverlay;
class UButton;
class UCanvasPanel;
class UTextBlock;
class UMainMenuManager;

UCLASS(Blueprintable)
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeOnInitialized() override;
	
public:
	//=================================================//
	//				Functions
	//=================================================//

	UFUNCTION() void OnPlayClicked();
	UFUNCTION() void OnSettingsClicked();
	UFUNCTION() void OnQuitClicked();
	UFUNCTION() void SetMainMenuManager(UMainMenuManager* NewMainMenuManager);
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	
	//=================================================//
	//				Components
	//=================================================//
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> TestTextBlock; 
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCanvasPanel> CanvasPanel;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> ButtonVerticalBoxHolder;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> StartGameButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> SettingsButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> QuitButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USizeBox> ButtonSizeBox;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UOverlay> UiHolder;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UBorder> BackgroundBorder;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UWidgetSwitcher> PanelSwitcher;
	
	//=================================================//
	//				references
	//=================================================//
	
	UPROPERTY() TObjectPtr<UMainMenuManager> MainMenuManager; 
};
