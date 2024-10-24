// Lukasz Dziedziczak 2024


#include "PlayerHealth.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UPlayerHealth::UPlayerHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	CurrentHealth = MaxHealth;
	
}


// Called every frame
void UPlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerHealth::TakeHealth(float Amount)
{
	if (!PlayerCharacter->IsAlive()) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0, MaxHealth);

	if (CurrentHealth == 0)
	{
		PlayerCharacter->Death();
	}
}

