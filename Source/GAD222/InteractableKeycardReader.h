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

public:
	virtual void Interact() override;
	
};
