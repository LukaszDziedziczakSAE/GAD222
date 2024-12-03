// Lukasz Dziedziczak 2024


#include "TutorialComponent.h"
#include "ZombieStoryHUD.h"
#include "UserWidget_Tutorial.h"
#include "ZombieGame_PlayerController.h"
#include "ZombieGameInstance.h"

// Sets default values for this component's properties
UTutorialComponent::UTutorialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	AZombieGame_PlayerController* PlayerController = Cast<AZombieGame_PlayerController>(GetOwner());
	if (PlayerController != nullptr) Widget = Cast<AZombieStoryHUD>(PlayerController->GetHUD())->TutorialWidget;
	
	Load();
}


// Called every frame
void UTutorialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UTutorialComponent::ShowLookTutorial()
{
	if (Widget == nullptr)
	{
		AZombieGame_PlayerController* PlayerController = Cast<AZombieGame_PlayerController>(GetOwner());
		if (PlayerController != nullptr) Widget = Cast<AZombieStoryHUD>(PlayerController->GetHUD())->TutorialWidget;
	}

	if (Widget != nullptr)
	{
		Widget->ShowLookTutorialText();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing TutorialWidget reference"));
	}
}

void UTutorialComponent::Save()
{
	UZombieGameInstance* ZombieGameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
	if (ZombieGameInstance != nullptr)
	{
		ZombieGameInstance->bHasLookedAround = bHasLookedAround;
		ZombieGameInstance->bHasMoved = bHasMoved;
		ZombieGameInstance->bHasSprinted = bHasSprinted;
		ZombieGameInstance->bHasEquipedWeapon = bHasEquipedWeapon;
		ZombieGameInstance->bHasReloaded = bHasReloaded;
		ZombieGameInstance->bHasAimed = bHasAimed;
		ZombieGameInstance->bHasFiredWeapon = bHasFiredWeapon;
	}
	else UE_LOG(LogTemp, Error, TEXT("Missing UZombieGameInstance on Saving tutorial bools"));
}

void UTutorialComponent::Load()
{
	UZombieGameInstance* ZombieGameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
	if (ZombieGameInstance != nullptr)
	{
		bHasLookedAround = ZombieGameInstance->bHasLookedAround;
		bHasMoved = ZombieGameInstance->bHasMoved;
		bHasSprinted = ZombieGameInstance->bHasSprinted;
		bHasEquipedWeapon = ZombieGameInstance->bHasEquipedWeapon;
		bHasReloaded = ZombieGameInstance->bHasReloaded;
		bHasAimed = ZombieGameInstance->bHasAimed;
		bHasFiredWeapon = ZombieGameInstance->bHasFiredWeapon;
	}
	else UE_LOG(LogTemp, Error, TEXT("Missing UZombieGameInstance on Loading tutorial bools"));
}

