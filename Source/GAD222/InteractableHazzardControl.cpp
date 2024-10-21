// Lukasz Dziedziczak 2024


#include "InteractableHazzardControl.h"
#include "Hazzard.h"

void AInteractableHazzardControl::Interact(APlayerCharacter* PlayerCharacter)
{
	Hazzard->ToggleHazzard();
	Super::Interact(PlayerCharacter);
}
