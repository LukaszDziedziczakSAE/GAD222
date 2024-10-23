// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZombieStoryHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API AZombieStoryHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void RemoveAllFromViewport();

	UFUNCTION(BlueprintNativeEvent)
	void SwitchToComputerView();

	UFUNCTION(BlueprintNativeEvent)
	void SwitchToPlayerView();
	
	UFUNCTION(BlueprintNativeEvent)
	void GamePaused();

	UFUNCTION(BlueprintNativeEvent)
	void GameUnpaused();
};
