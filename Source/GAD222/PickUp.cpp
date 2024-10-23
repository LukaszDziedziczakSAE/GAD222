// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "PlayerCharacter.h"
#include "WeaponManagerComponent.h"
#include "PlayerInteraction.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(Mesh);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Mesh);
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUp::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		PickUp(PlayerCharacter);
	}
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
	if (PlayerCharacter->WeaponManagerComponent->HasPistol) return;

	PlayerCharacter->WeaponManagerComponent->HasPistol = true;

	Destroy();
}

void APickUp::PickupPistolAmmo(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->WeaponManagerComponent->PistolAmmoStorage += Amount;

	Destroy();
}

void APickUp::PickupKeycard(APlayerCharacter* PlayerCharacter, int KeycardLevel)
{
	if (PlayerCharacter->PlayerInteraction->KeycardLevel < KeycardLevel)
	{
		PlayerCharacter->PlayerInteraction->KeycardLevel = KeycardLevel;
	}

	Destroy();
}

