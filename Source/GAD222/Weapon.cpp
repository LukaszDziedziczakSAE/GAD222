// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ZombieCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeaponManagerComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(WeaponMesh);

	MuzzleFlash = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle FLash"));
	MuzzleFlash->SetupAttachment(WeaponMesh);
	MuzzleFlash->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeSinceLastFire < FireRate)
	{
		TimeSinceLastFire += DeltaTime;
	}
}

void AWeapon::Fire()
{
	if (TimeSinceLastFire < FireRate) return;


	//UE_LOG(LogTemp, Warning, TEXT("%s Firing"), *GetName());

	UGameplayStatics::PlaySoundAtLocation(this, FireSoundCue, GetActorLocation());

	UNiagaraFunctionLibrary::SpawnSystemAttached(FireEffectMuzzle, Muzzle, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);

	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.bTraceIntoSubComponents = true;

	//Re-initialize hit info
	FHitResult HitResult(ForceInit);

	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector StartVariated = FVector{
		UKismetMathLibrary::RandomFloatInRange(Start.X - Variation, Start.X + Variation),
		UKismetMathLibrary::RandomFloatInRange(Start.Y - Variation, Start.Y + Variation),
		UKismetMathLibrary::RandomFloatInRange(Start.Z - Variation, Start.Z + Variation)
	};
	FVector End = StartVariated + (PlayerCameraManager->GetActorForwardVector() * TraceLength);

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,		//result
		Start,	//start
		End, //end
		ECC_GameTraceChannel1, //collision channel (ECC_GameTraceChannel1)
		TraceParams
	))
	{
		USkeletalMeshComponent* HitSkeletalMeshComponent = Cast<USkeletalMeshComponent>(HitResult.GetComponent());
		AZombieCharacter* Zombie = Cast<AZombieCharacter>(HitResult.GetActor());

		FRotator ImpactRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.ImpactPoint);

		FActorSpawnParameters SpawnParameters;
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectilePrefab, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation(), SpawnParameters);

		

		if (Zombie != nullptr && HitSkeletalMeshComponent != nullptr)
		{
			Zombie->InflictDamage(Damage, HitSkeletalMeshComponent);
			/*UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactFlesh, HitResult.Location, ImapctRotation);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactFleshAudio, HitResult.Location);*/

			Projectile->Initilize(ProjectileSpeed, HitResult.Location, ImpactRotation, ImpactFlesh, ImpactFleshAudio);
		}
		else
		{
			/*UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Impact, HitResult.Location, ImapctRotation);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactAudio, HitResult.Location);*/

			Projectile->Initilize(ProjectileSpeed, HitResult.Location, ImpactRotation, Impact, ImpactAudio);
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.GetComponent()->GetName());
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}

	TimeSinceLastFire = 0;
	WeaponManagerComponent->PistolAmmo -= 1;

	MuzzleFlash->Activate(true);
}

void AWeapon::Reload()
{
	int AmmoNeeded = MaxAmmo - WeaponManagerComponent->PistolAmmo;
	int ReloadAmount = FMath::Clamp(AmmoNeeded, 0, WeaponManagerComponent->PistolAmmoStorage);

	WeaponManagerComponent->PistolAmmoStorage -= ReloadAmount;
	WeaponManagerComponent->PistolAmmo += ReloadAmount;
}

