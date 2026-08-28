// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainMenuInstance.generated.h"

class UMainMenuManager;

UCLASS()
class UMainMenuInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	
	UMainMenuManager* GetMainMenuManager() const;
private:
	UPROPERTY() TObjectPtr<UMainMenuManager> MainMenuManager;
};
