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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FComputerInfoItem> ComputerInfoItems;

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual bool CanInteract(APlayerCharacter* PlayerCharacter) override;
	
};
