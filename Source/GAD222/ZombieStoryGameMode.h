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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class APlayerCharacter> Maria;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APlayerCharacter> Mike;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ULevelSequence* IntroLevelSequence;

	UFUNCTION()
	void IntroLevelSequenceComplete();

public:
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/** Returns default pawn class for given controller */
	UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class APlayerStart*> PlayerStarts;

	UFUNCTION(BlueprintCallable)
	void ReloadGameLevelFromCheckpoint();

	UFUNCTION(BlueprintCallable)
	void ReloadGameLevel();
	
	UFUNCTION(BlueprintCallable)
	void ReloadMainMenu();
};
