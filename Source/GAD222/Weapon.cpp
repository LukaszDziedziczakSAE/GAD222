// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(WeaponMesh);
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

}

void AWeapon::Fire()
{
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
	FVector End = Start + (PlayerCameraManager->GetActorForwardVector() * TraceLength);

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,		//result
		Start,	//start
		End, //end
		ECC_GameTraceChannel1, //collision channel
		TraceParams
	))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		USkeletalMeshComponent* HitSkeletalMeshComponent = Cast<USkeletalMeshComponent>(HitComponent);
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitComponent->GetName());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Impact, HitResult.Location);

		if (HitComponent->GetName() != "CharacterMesh0")
		{
			HitSkeletalMeshComponent->Stop();
			HitComponent->DetachFromParent(true);
			HitComponent->SetSimulatePhysics(true);
		}
		
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}
}

