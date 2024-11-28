// Lukasz Dziedziczak 2024


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "ZombieGame_PlayerController.h"
#include "ZombieGameInstance.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Sphere"));
	SetRootComponent(Trigger);
	Trigger->SetBoxExtent(FVector{ 400, 50, 200 });
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance != nullptr)
		{
			GameInstance->Checkpoint = CheckpointIndex;
			UE_LOG(LogTemp, Display, TEXT("Checkpoint %d"), CheckpointIndex);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Checkpoint could not find GameInstance"));
		}
		Destroy();
	}
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

