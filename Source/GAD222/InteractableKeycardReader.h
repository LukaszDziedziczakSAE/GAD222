// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableKeycardReader.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API AInteractableKeycardReader : public AInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ADoor* Door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SecutiyLevel;

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	virtual bool CanInteract(APlayerCharacter* PlayerCharacter) override;
	
};
