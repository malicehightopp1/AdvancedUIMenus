
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

class AMainMenuCamera;
class UMainMenuWidget;
class USettingsWidget;

UCLASS()
class AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainMenuGameMode();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI") TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI") TSubclassOf<USettingsWidget> SettingsWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI") TObjectPtr<AMainMenuCamera> MainMenuCamera;
};
