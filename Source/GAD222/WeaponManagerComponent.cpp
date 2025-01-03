// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManagerComponent.h"
#include "Weapon.h"
#include "PlayerCharacter.h"
#include "ZombieGameInstance.h"
#include "ZombieGame_PlayerController.h"
#include "TutorialComponent.h"

// Sets default values for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	PlayerController = Cast<AZombieGame_PlayerController>(PlayerCharacter->GetController());
}


void UWeaponManagerComponent::ReloadAnimationComplete()
{
	bIsReloading = false;
}

// Called every frame
void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponManagerComponent::EquipWeapon()
{
	if (!HasPistol || bIsReloading) return;

	if (CurrentWeapon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Equiping Weapon"));
		SpawnWeapon();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unequiping Weapon"));
		DespawnWeapon();
	}

	PlayerCharacter->SetMovementSpeed();
}

void UWeaponManagerComponent::UnequipWeapon()
{

}

void UWeaponManagerComponent::SpawnWeapon()
{
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(Weapons[0].Weapon);
	CurrentWeapon->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Hand_Right"));
	CurrentWeapon->SetActorRelativeLocation(Weapons[0].RelativeLocation);
	CurrentWeapon->SetActorRelativeRotation(Weapons[0].RelativeRotation);
	CurrentWeapon->SetWeaponManagerComponent(this);
	CurrentWeapon->SetOwner(GetOwner());

	WeaponEquipedTutorial(PistolAmmoStorage > 0);
}

void UWeaponManagerComponent::DespawnWeapon()
{
	CurrentWeapon->Destroy();
	CurrentWeapon = nullptr;

	WeaponUnequipedTutorial();
}

void UWeaponManagerComponent::PullTrigger()
{
	if (CurrentWeapon == nullptr || bIsReloading) return;

	if (PistolAmmo == 0)
	{
		ReloadCurrentWeapon();
		return;
	}

	CurrentWeapon->Fire();
	PlayerCharacter->PlayAnimMontage(CurrentWeapon->WeaponFire);
}

void UWeaponManagerComponent::ReleaseTrigger()
{
	
}

void UWeaponManagerComponent::ReloadCurrentWeapon()
{
	if (CurrentWeapon == nullptr ||
		CurrentWeapon->GetMaxAmmo() == PistolAmmo ||
		PistolAmmoStorage == 0 ||
		bIsReloading)
		return;

	float t = PlayerCharacter->PlayAnimMontage(CurrentWeapon->WeaponReload);
	bIsReloading = true;
	FTimerHandle AttackTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UWeaponManagerComponent::ReloadAnimationComplete, t, false);

	WeaponReloadedTutorial();
}

void UWeaponManagerComponent::Save()
{
	UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance != nullptr)
	{
		GameInstance->PistolAmmo = PistolAmmo;
		GameInstance->PistolAmmoStorage = PistolAmmoStorage;
	}
}

void UWeaponManagerComponent::WeaponPickedUpTutorial()
{
	if (PlayerController != nullptr) PlayerController->TutorialWeaponPickedUp();
}

void UWeaponManagerComponent::WeaponEquipedTutorial(bool bHasAmmo)
{
	if (PlayerController != nullptr) PlayerController->TutorialWeaponEquiped(bHasAmmo);
}

void UWeaponManagerComponent::WeaponUnequipedTutorial()
{
	if (PlayerController != nullptr) PlayerController->TutorialWeaponUnequiped();
}

void UWeaponManagerComponent::WeaponReloadedTutorial()
{
	if (PlayerController != nullptr) PlayerController->TutorialWeaponReloaded();
}

