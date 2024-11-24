// Lukasz Dziedziczak 2024


#include "MusicTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Music.h"

// Sets default values
AMusicTrigger::AMusicTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Sphere"));
	SetRootComponent(Trigger);
	Trigger->SetBoxExtent(FVector{600, 200, 200});
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMusicTrigger::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMusicTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Music = Cast<AMusic>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusic::StaticClass()));
	if (Music == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Music Actor not found"));
	}
}

void AMusicTrigger::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bActive) return;

	RunAction(Action1);
	RunAction(Action2);
	RunAction(Action3);
	RunAction(Action4);

	Destroy();
}

void AMusicTrigger::RunAction(TEnumAsByte<ETriggerAction> Action)
{
	switch (Action)
	{
	case FadeIn_Percussive:
		Music->FadeInPercussive();
		break;

	case FadeOut_Percussive:
		Music->FadeOutPercussive();
		break;

	case FadeIn_Atmospheric:
		Music->FadeInAtmospheric();
		break;

	case FadeOut_Atmospheric:
		Music->FadeOutAtmospheric();
		break;

	case FadeIn_Piano:
		Music->FadeInPiano();
		break;

	case FadeOut_Piano:
		Music->FadeOutPiano();
		break;

	case FadeIn_Bongos:
		Music->FadeInBongos();
		break;

	case FadeOut_Bongos:
		Music->FadeOutBongos();
		break;

	case FadeIn_Strings:
		Music->FadeInStrings();
		break;

	case FadeOut_Strings:
		Music->FadeOutStrings();
		break;

	case FadeIn_SquareWave:
		Music->FadeInSquareWave();
		break;

	case FadeOut_SquareWave:
		Music->FadeOutSquareWave();
		break;
	}
}

// Called every frame
void AMusicTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusicTrigger::Activate()
{
	bActive = true;
}

