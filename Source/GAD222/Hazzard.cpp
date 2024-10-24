// Lukasz Dziedziczak 2024


#include "Hazzard.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "ZombieCharacter.h"

// Sets default values
AHazzard::AHazzard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComp);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AHazzard::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AHazzard::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AHazzard::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<USceneComponent*> ChildrenComponents;
	RootComp->GetChildrenComponents(true, ChildrenComponents);
	for (USceneComponent* Component : ChildrenComponents)
	{
		UParticleSystemComponent* ParticleSystem = Cast<UParticleSystemComponent>(Component);

		if (ParticleSystem != nullptr)
		{
			Effects.Add(ParticleSystem);
		}
	}

	if (bHazzardIsActive) TurnOnHazzard();
	else TurnOffHazzard();
}

void AHazzard::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s entered hazzard"), *Character->GetName());
		CharactersInHazzard.Add(Character);
	}
}

void AHazzard::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s exited hazzard"), *Character->GetName());
		CharactersInHazzard.Remove(Character);
	}
}

// Called every frame
void AHazzard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHazzardIsActive) return;

	for (ACharacter* Character : CharactersInHazzard)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(Character);
		if (Player != nullptr)
		{
			Player->InflictDamage(DamageRate * DeltaTime);
		}
		else
		{
			AZombieCharacter* Zombie = Cast<AZombieCharacter>(Character);
			if (Zombie != nullptr)
			{
				Zombie->InflictDamage(DamageRate * DeltaTime);
				Zombie->StartBurning();
			}
		}
	}
}

void AHazzard::TurnOnHazzard()
{
	for (UParticleSystemComponent* ParticleSystem : Effects)
	{
		ParticleSystem->Activate(true);
	}

	AudioComponent->Play();

	bHazzardIsActive = true;
}

void AHazzard::TurnOffHazzard()
{
	for (UParticleSystemComponent* ParticleSystem : Effects)
	{
		ParticleSystem->Deactivate();
	}

	AudioComponent->Stop();

	bHazzardIsActive = false;
}

void AHazzard::ToggleHazzard()
{
	if (bHazzardIsActive) TurnOffHazzard();
	else TurnOnHazzard();
}

