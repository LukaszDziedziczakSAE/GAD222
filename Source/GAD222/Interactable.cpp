// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "PlayerInteraction.h"
#include "Components/AudioComponent.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(Mesh);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnOverlapEnd);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Mesh);
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractable::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->PlayerInteraction->Interactable = this;
	}
}

void AInteractable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter != nullptr && PlayerCharacter->PlayerInteraction->Interactable == this)
	{
		PlayerCharacter->PlayerInteraction->Interactable = nullptr;
	}
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::Interact(APlayerCharacter* PlayerCharacter)
{
	AudioComponent->Play();
}

bool AInteractable::CanInteract(APlayerCharacter* PlayerCharacter)
{
	return true;
}

