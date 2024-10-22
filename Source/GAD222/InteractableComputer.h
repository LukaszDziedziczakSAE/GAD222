// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableComputer.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API AInteractableComputer : public AInteractable
{
	GENERATED_BODY()

public:
	AInteractableComputer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* VideoScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMediaSoundComponent* MediaSoundComponent;

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual bool CanInteract(APlayerCharacter* PlayerCharacter) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FComputerInfoItem> ComputerInfoItems;

	UFUNCTION(BlueprintCallable)
	void PlayVideo(class UMediaSource* Media);

	UFUNCTION(BlueprintCallable)
	void FinishVideo();
};
