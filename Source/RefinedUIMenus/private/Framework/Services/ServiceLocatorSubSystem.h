// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServiceLocatorSubSystem.generated.h"

class UMainMenuManager;
/**
 * 
 */
UCLASS()
class UServiceLocatorSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	static UServiceLocatorSubSystem* Get(const UObject* WorldContextObject);
	
	UMainMenuManager* GetMainMenuManager() const;
	
private:
	UPROPERTY() TObjectPtr<UMainMenuManager> MainMenuManager; //the service locator owns this reference
};
