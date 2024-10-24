// Lukasz Dziedziczak 2024


#include "LevelEnd.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "ZombieStoryHUD.h"

// Sets default values
ALevelEnd::ALevelEnd()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALevelEnd::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelEnd::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr)
	{
		AZombieStoryHUD* HUD = Cast<AZombieStoryHUD>(Cast<APlayerController>(Player->GetController())->GetHUD());
		if (HUD != nullptr)
		{
			HUD->RemoveAllFromViewport();
			HUD->LevelEnd();
			Player->GetMesh()->Stop();
		}
	}
}

// Called every frame
void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

