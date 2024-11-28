// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieStoryGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "ZombieGame_PlayerController.h"
#include "ZombieGameInstance.h"

void AZombieStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerStarts.Num() == 0)
	{
		TArray<AActor*> StartActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), StartActors);
		for (AActor* StartActor : StartActors)
		{
			APlayerStart* PS = Cast<APlayerStart>(StartActor);
			if (PS == nullptr) continue;
			PlayerStarts.Add(PS);
		}
	}
}

AActor* AZombieStoryGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	/*AZombieGame_PlayerController* PController = Cast<AZombieGame_PlayerController>(Player);
	FName CheckpointName = FName(FString::FromInt(PController->Checkpoint));*/
	if (PlayerStarts.Num() == 0)
	{
		TArray<AActor*> StartActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), StartActors);
		for (AActor* StartActor : StartActors)
		{
			APlayerStart* PS = Cast<APlayerStart>(StartActor);
			if (PS == nullptr) continue;
			PlayerStarts.Add(PS);
		}
	}

	FName CheckpointName = FName(FString::FromInt(0));

	UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetGameInstance());
	if (GameInstance != nullptr)
	{
		CheckpointName = FName(FString::FromInt(GameInstance->Checkpoint));
	}
	else UE_LOG(LogTemp, Error, TEXT("GameInstance is null"));

	for (APlayerStart* PStart : PlayerStarts)
	{
		if (PStart->PlayerStartTag == CheckpointName)
		{
			return PStart;
		}
	}

	Super::ChoosePlayerStart_Implementation(Player);
	UE_LOG(LogTemp, Error, TEXT("Did not find checkpoint PlayerStart"));
	return PlayerStarts[0];
}

void AZombieStoryGameMode::ReloadGameLevelFromCheckpoint()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_PineGap_Sublevel44"));
}

void AZombieStoryGameMode::ReloadGameLevel()
{
	UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetGameInstance());
	if (GameInstance != nullptr) GameInstance->Reset();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_PineGap_Sublevel44"));
}

void AZombieStoryGameMode::ReloadMainMenu()
{
	UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetGameInstance());
	if (GameInstance != nullptr) GameInstance->Reset();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_Coolroom"));
}
