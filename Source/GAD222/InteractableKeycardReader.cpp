// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableKeycardReader.h"
#include "Door.h"

void AInteractableKeycardReader::Interact()
{
	if (Door != nullptr)
	{
		Door->IsLocked = false;
	}

	Super::Interact();
}
