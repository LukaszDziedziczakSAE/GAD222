// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComputer.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"

AInteractableComputer::AInteractableComputer()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(GetRootComponent());
}

void AInteractableComputer::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!CanInteract(PlayerCharacter)) return;

	UE_LOG(LogTemp, Warning, TEXT("Switching to Computer Interaction"));

	PlayerCharacter->SwitchCamera(this);
}

bool AInteractableComputer::CanInteract(APlayerCharacter* PlayerCharacter)
{
	return !PlayerCharacter->bInComputerView;
}
