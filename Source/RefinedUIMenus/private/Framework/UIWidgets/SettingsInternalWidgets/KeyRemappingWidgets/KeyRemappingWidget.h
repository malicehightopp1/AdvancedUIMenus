// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyRemappingWidget.generated.h"

class UInputIconData;
class UInputMappingManager;
class UVerticalBox;
class UKeyRemappingRowWidget;

USTRUCT(BlueprintType)
struct FRemappableInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName MappingName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
};
UCLASS()
class UKeyRemappingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Input remapping") TArray<FRemappableInput> RemappableInputs; 
	void SetRemappingManager(UInputMappingManager* InRemappingManager);
	void BuildRemappingList();
protected:
    
        virtual void NativeConstruct() override;
    
        UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> RemappingList;
    
        UPROPERTY(EditAnywhere, Category = "Remapping") TSubclassOf<UKeyRemappingRowWidget> KeyRemappingRowClass;
    
private:
    
        UPROPERTY() UInputMappingManager* RemappingManager = nullptr;
		
		UPROPERTY(EditAnywhere, Category = "Remapping") TObjectPtr<UInputIconData> InputIconData;
	
};
