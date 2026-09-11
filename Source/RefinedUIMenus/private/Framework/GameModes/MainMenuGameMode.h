
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

class AMainMenuCamera;
class UMainMenuWidget;
class USettingsWidget;
class USoundClass;
class USoundMix; 

UCLASS()
class AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainMenuGameMode();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI") TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI") TSubclassOf<USettingsWidget> SettingsWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI") TObjectPtr<AMainMenuCamera> MainMenuCamera;
	
	//audio
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")TObjectPtr<USoundClass> MasterSoundClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")TObjectPtr<USoundClass> MusicSoundClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")TObjectPtr<USoundClass> SFXSoundClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")TObjectPtr<USoundMix> SettingsSoundMix;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")USoundBase* MainMenuMusic;
};
