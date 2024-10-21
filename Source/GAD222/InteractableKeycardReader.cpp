// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableKeycardReader.h"
#include "Door.h"
#include "PlayerCharacter.h"
#include "PlayerInteraction.h"

void AInteractableKeycardReader::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!CanInteract(PlayerCharacter)) return;

	if (Door != nullptr)
	{
		Door->bIsLocked = false;
	}

	Super::Interact(PlayerCharacter);
}

bool AInteractableKeycardReader::CanInteract(APlayerCharacter* PlayerCharacter)
{
	return PlayerCharacter->PlayerInteraction->KeycardLevel >= SecutiyLevel;
}
