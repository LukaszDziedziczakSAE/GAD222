// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombieStoryGameMode.generated.h"

UCLASS()
class GAD222_API AZombieStoryGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class APlayerStart*> PlayerStarts;

	UFUNCTION(BlueprintCallable)
	void ReloadGameLevel();

	UFUNCTION(BlueprintCallable)
	void RespawnCharacter();
	
	UFUNCTION(BlueprintCallable)
	void ReloadMainMenu();
};
