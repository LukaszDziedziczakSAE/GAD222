// Lukasz Dziedziczak 2024


#include "ZombieHealth.h"
#include "ZombieCharacter.h"

// Sets default values for this component's properties
UZombieHealth::UZombieHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZombieHealth::BeginPlay()
{
	Super::BeginPlay();

	ZombieCharacter = Cast<AZombieCharacter>(GetOwner());

	CurrentHealth = MaxHealth;
	HeadHealth = MaxHeadHealth;
	LeftArmHealth = MaxArmHealth;
	RightArmHealth = MaxArmHealth;
	LeftLegHealth = MaxLegHealth;
	RightLegHealth = MaxLegHealth;
}


// Called every frame
void UZombieHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UZombieHealth::TakeHealth(float Amount, EBodyPart BodyPart)
{
	if (!ZombieCharacter->IsAlive()) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0, MaxHealth);

	switch (BodyPart)
	{
	case Torso:
		break;
	case Head:
		HeadHealth = FMath::Clamp(HeadHealth - Amount, 0, MaxHeadHealth);
		break;
	case LeftArm:
		LeftArmHealth = FMath::Clamp(LeftArmHealth - Amount, 0, MaxArmHealth);
		break;
	case RightArm:
		RightArmHealth = FMath::Clamp(RightArmHealth - Amount, 0, MaxArmHealth);
		break;
	case Leftleg:
		LeftLegHealth = FMath::Clamp(LeftLegHealth - Amount, 0, MaxLegHealth);
		break;
	case RightLeg:
		RightLegHealth = FMath::Clamp(RightLegHealth - Amount, 0, MaxLegHealth);
		break;
	default:
		break;
	}

	if (CurrentHealth == 0)
	{
		ZombieCharacter->Death();
	}
	
}

