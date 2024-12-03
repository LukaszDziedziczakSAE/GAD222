// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Tutorial.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API UUserWidget_Tutorial : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ShowLookTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void HideLookTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void ShowMoveTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void HideMoveTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void ShowSprintTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void HideSprintTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void ShowEquipTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void HideEquipTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void ShowReloadTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void HideReloadTutorialText();

	UFUNCTION(BlueprintNativeEvent)
	void ShowAimingTextTutorial();

	UFUNCTION(BlueprintNativeEvent)
	void HideAimingTextTutorial();

	UFUNCTION(BlueprintNativeEvent)
	void ShowFiringTextTutorial();

	UFUNCTION(BlueprintNativeEvent)
	void HideFiringTextTutorial();

	UFUNCTION(BlueprintNativeEvent)
	void ShowZombieStrugleTextTutorial();

	UFUNCTION(BlueprintNativeEvent)
	void HideZombieStrugleTextTutorial();
};
