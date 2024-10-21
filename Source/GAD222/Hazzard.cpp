// Lukasz Dziedziczak 2024


#include "Hazzard.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

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

}

void AHazzard::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void AHazzard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

