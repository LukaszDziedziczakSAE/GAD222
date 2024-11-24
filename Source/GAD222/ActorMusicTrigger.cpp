// Lukasz Dziedziczak 2024


#include "ActorMusicTrigger.h"
#include "ZombieCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Music.h"

// Sets default values for this component's properties
UActorMusicTrigger::UActorMusicTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorMusicTrigger::BeginPlay()
{
	Super::BeginPlay();

	Music = Cast<AMusic>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusic::StaticClass()));
	if (Music == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Music Actor not found"));
	}

	Zombie = Cast<AZombieCharacter>(GetOwner());
	Zombie->ZombieDeathEvent.AddDynamic(this, &UActorMusicTrigger::OnZombieDeath);
}


void UActorMusicTrigger::OnZombieDeath()
{
	RunAction(Action1);
	RunAction(Action2);
	RunAction(Action3);
	RunAction(Action4);
}

void UActorMusicTrigger::RunAction(TEnumAsByte<ETriggerAction> Action)
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
void UActorMusicTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

