// Lukasz Dziedziczak 2024


#include "ZombieGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PickUp.h"
#include "PlayerCharacter.h"
#include "PlayerInteraction.h"
#include "WeaponManagerComponent.h"

void UZombieGameInstance::AddPickup(FString Name)
{
	if (!Pickups.Contains(Name))
	{
		Pickups.Add(Name);
	}
}

void UZombieGameInstance::PlayerCharacterStart(APlayerCharacter* PlayerCharacter)
{
	const bool SKIP_NOTIFICATION = true;

	TArray<AActor*> PickupActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickUp::StaticClass(), PickupActors);
	
	for (FString Name : Pickups)
	{
		for (AActor* PickupActor : PickupActors)
		{
			APickUp* PickUp = Cast<APickUp>(PickupActor);
			if (PickUp != nullptr && Name == PickUp->GetName())
			{
				PickUp->PickUp(PlayerCharacter, SKIP_NOTIFICATION);
				continue;
			}
		}
	}

	PlayerCharacter->PlayerInteraction->KeycardLevel = KeycardLevel;
	PlayerCharacter->WeaponManagerComponent->PistolAmmo = PistolAmmo;
	PlayerCharacter->WeaponManagerComponent->PistolAmmoStorage = PistolAmmoStorage;
	PlayerCharacter->Clothed(bHasClothesOn);

	TArray<AActor*> DoorActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoor::StaticClass(), DoorActors);
	for (AActor* DoorActor : DoorActors)
	{
		ADoor* Door = Cast<ADoor>(DoorActor);
		if (Door != nullptr && Door->bSaveState)
		{
			Door->InitilizeDoor(DoorState);
		}
	}
}

void UZombieGameInstance::Reset()
{
	Checkpoint = 0;
	KeycardLevel = 0;
	PistolAmmo = 0;
	PistolAmmoStorage = 0;
	Pickups.Empty();
	bHasClothesOn = false;
	DoorState = DoorClosed;
}
