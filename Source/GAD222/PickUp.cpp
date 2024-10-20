// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "PlayerCharacter.h"
#include "WeaponManagerComponent.h"
#include "PlayerInteraction.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUp::PickUp(APlayerCharacter* PlayerCharacter)
{
	switch (PickUpType)
	{
	case PistolPickup:
		PickupPistol(PlayerCharacter);
		break;

	case PistolAmmoPickup:
		PickupPistolAmmo(PlayerCharacter);
		break;

	case ClothingPickup:
		break;

	case Keycard1Pickup:
		PickupKeycard(PlayerCharacter, 1);
	}
}

void APickUp::PickupPistol(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->WeaponManagerComponent->HasPistol = true;
}

void APickUp::PickupPistolAmmo(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->WeaponManagerComponent->PistolAmmo += Amount;
}

void APickUp::PickupKeycard(APlayerCharacter* PlayerCharacter, int KeycardLevel)
{
	if (PlayerCharacter->PlayerInteraction->KeycardLevel < KeycardLevel)
	{
		PlayerCharacter->PlayerInteraction->KeycardLevel = KeycardLevel;
	}
}

