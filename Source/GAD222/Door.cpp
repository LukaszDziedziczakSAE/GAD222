// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ZombieGameInstance.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(RootComp);

	DoorMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh 2"));
	DoorMesh2->SetupAttachment(RootComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComp);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);

	OpenEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Open Effect"));
	OpenEffect->SetupAttachment(RootComp);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComp);
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (DoorMesh->GetStaticMesh() != nullptr)
	{
		ClosedPosition = DoorMesh->GetRelativeLocation();
	}

	if (DoorMesh2->GetStaticMesh() != nullptr)
	{
		ClosedPosition2 = DoorMesh2->GetRelativeLocation();
	}

	DoorState = DoorClosed;
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == nullptr) return;

	OverlappingActors.Add(OtherActor);
}

void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacter>(OtherActor) == nullptr) return;

	OverlappingActors.Remove(OtherActor);
}

void ADoor::OpeningTick()
{
	float Progress = (ActionTimer / OpeningTime);

	if (ActionTimer >= OpeningTime)
	{
		Progress = 1.0f;
		DoorState = DoorOpen;
	}


	if (DoorMesh->GetStaticMesh() != nullptr)
	{
		FVector DoorMeshPosition = FMath::Lerp(ClosedPosition, OpenPosition, Progress);
		DoorMesh->SetRelativeLocation(DoorMeshPosition);
	}

	if (DoorMesh2->GetStaticMesh() != nullptr)
	{
		FVector DoorMeshPosition2 = FMath::Lerp(ClosedPosition2, OpenPosition2, Progress);
		DoorMesh2->SetRelativeLocation(DoorMeshPosition2);
	}

	if (bSaveState && Progress == 1.0f)
	{
		UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance != nullptr)
		{
			GameInstance->DoorState = DoorState;
		}
	}
}

void ADoor::ClosingTick()
{
	float Progress = (ActionTimer / OpeningTime);

	if (ActionTimer >= OpeningTime)
	{
		Progress = 1.0f;
		DoorState = DoorClosed;

		if (bLockOnClose)
		{
			bIsLocked = true;
		}
	}


	if (DoorMesh->GetStaticMesh() != nullptr)
	{
		FVector DoorMeshPosition = FMath::Lerp(OpenPosition, ClosedPosition, Progress);
		DoorMesh->SetRelativeLocation(DoorMeshPosition);
	}

	if (DoorMesh2->GetStaticMesh() != nullptr)
	{
		FVector DoorMeshPosition2 = FMath::Lerp(OpenPosition2, ClosedPosition2, Progress);
		DoorMesh2->SetRelativeLocation(DoorMeshPosition2);
	}

	if (bSaveState && Progress == 1.0f)
	{
		UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance != nullptr)
		{
			GameInstance->DoorState = DoorState;
		}
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (DoorState)
	{
	case DoorOpening:
		ActionTimer += DeltaTime;
		OpeningTick();
		break;

	case DoorClosing:
		ActionTimer += DeltaTime;
		ClosingTick();
		break;

	case DoorOpen:
		if (!bManualOverride && OverlappingActors.Num() == 0)
		{
			CloseDoor();
		}
		break;

	case DoorClosed:
		if (!bManualOverride && OverlappingActors.Num() > 0 && !bIsLocked)
		{
			OpenDoor();
		}
		break;
	}
}

void ADoor::OpenDoor()
{
	ActionTimer = 0;
	DoorState = DoorOpening;

	if (OpenEffect->Template != nullptr)
	{
		OpenEffect->Activate(true);
	}

	AudioComponent->SetSound(OpeningSound);
	AudioComponent->Play();
}

void ADoor::CloseDoor()
{
	ActionTimer = 0;
	DoorState = DoorClosing;

	if (OpenEffect->Template != nullptr)
	{
		OpenEffect->Deactivate();
	}

	AudioComponent->SetSound(ClosingSound);
	AudioComponent->Play();
}

void ADoor::InitilizeDoor(TEnumAsByte<EDoorState> State)
{
	if (State == DoorOpen)
	{
		float Progress = 0;
		DoorState = DoorOpen;

		if (DoorMesh->GetStaticMesh() != nullptr)
		{
			FVector DoorMeshPosition = FMath::Lerp(OpenPosition, ClosedPosition, Progress);
			DoorMesh->SetRelativeLocation(DoorMeshPosition);
		}

		if (DoorMesh2->GetStaticMesh() != nullptr)
		{
			FVector DoorMeshPosition2 = FMath::Lerp(OpenPosition2, ClosedPosition2, Progress);
			DoorMesh2->SetRelativeLocation(DoorMeshPosition2);
		}
	}

	else if (State == DoorClosed)
	{
		float Progress = 1;
		DoorState = DoorClosed;

		if (DoorMesh->GetStaticMesh() != nullptr)
		{
			FVector DoorMeshPosition = FMath::Lerp(OpenPosition, ClosedPosition, Progress);
			DoorMesh->SetRelativeLocation(DoorMeshPosition);
		}

		if (DoorMesh2->GetStaticMesh() != nullptr)
		{
			FVector DoorMeshPosition2 = FMath::Lerp(OpenPosition2, ClosedPosition2, Progress);
			DoorMesh2->SetRelativeLocation(DoorMeshPosition2);
		}
	}
}

