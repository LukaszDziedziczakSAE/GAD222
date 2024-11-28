// Lukasz Dziedziczak 2024


#include "InteractableHazzardControl.h"
#include "Hazzard.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"


AInteractableHazzardControl::AInteractableHazzardControl()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(Mesh);*/
	//CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractableHazzardControl::OnOverlapBegin);
	//CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractableHazzardControl::OnOverlapEnd);

	/*AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Mesh);
	AudioComponent->bAutoActivate = false;*/

	ValvePivot = CreateDefaultSubobject<USceneComponent>(TEXT("Valve Pivot"));
	ValvePivot->SetupAttachment(Mesh);

	Valve = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Valve"));
	Valve->SetupAttachment(ValvePivot);
}

void AInteractableHazzardControl::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(newComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AInteractableHazzardControl::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void AInteractableHazzardControl::Tick(float DeltaTime)
{


	Super::Tick(DeltaTime);

	if (HazzardControlState == Openning)
	{
		CurrentTransitionTime += DeltaTime;
		float CurrentAngle;
		if (CurrentTransitionTime < TransitionTime)
		{
			CurrentAngle = FMath::Lerp(ClosedAngle, OpenAngle, (CurrentTransitionTime / TransitionTime));
		}
		else
		{
			CurrentAngle = FMath::Lerp(ClosedAngle, OpenAngle, 1.0f);
			HazzardControlState = Open;
		}
		ValvePivot->SetRelativeRotation(FRotator::MakeFromEuler(FVector{ 0, 0, CurrentAngle }));
		//UE_LOG(LogTemp, Warning, TEXT("Angle: %f, Rotation: %s"), CurrentAngle, *ValvePivot->GetRelativeRotation().ToString());
	}

	else if (HazzardControlState == Closing)
	{
		CurrentTransitionTime += DeltaTime;
		float CurrentAngle;
		if (CurrentTransitionTime < TransitionTime)
		{
			CurrentAngle = FMath::Lerp(OpenAngle, ClosedAngle, (CurrentTransitionTime / TransitionTime));
		}
		else
		{
			CurrentAngle = FMath::Lerp(OpenAngle, ClosedAngle, 1.0f);
			HazzardControlState = Closed;
		}
		ValvePivot->SetRelativeRotation(FRotator::MakeFromEuler(FVector{ 0, 0, CurrentAngle }));
		//UE_LOG(LogTemp, Warning, TEXT("Angle: %f, Rotation: %s"), CurrentAngle, *ValvePivot->GetRelativeRotation().ToString());
	}
}

void AInteractableHazzardControl::Interact(APlayerCharacter* PlayerCharacter)
{
	if (HazzardControlState == Open)
	{
		Hazzard->ToggleHazzard();
		CurrentTransitionTime = 0;
		HazzardControlState = Closing;
	}

	else if (HazzardControlState == Closed)
	{
		CurrentTransitionTime = 0;
		HazzardControlState = Openning;
		Hazzard->ToggleHazzard();
	}

	
	Super::Interact(PlayerCharacter);
}
