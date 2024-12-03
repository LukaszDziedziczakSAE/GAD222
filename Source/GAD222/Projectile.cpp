// Lukasz Dziedziczak 2024


#include "Projectile.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Projectile Effect"));
	SetRootComponent(ProjectileEffect);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::SpawnImpact()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, ImpactLocation, ImpactRotation);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactAudio, ImpactLocation);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileSpeed > 0)
	{
		SetActorLocation(
			GetActorLocation() + 
			(GetActorForwardVector() * ProjectileSpeed * DeltaTime) 
		);

		TimeToTarget -= DeltaTime;

		if (TimeToTarget <= 0)
		{
			SpawnImpact();
			Destroy();
		}
	}
}

void AProjectile::Initilize(float Speed, FVector Location, FRotator Rotation, UNiagaraSystem* Effect, USoundBase* Audio)
{
	ProjectileSpeed = Speed;
	float Distance = FVector::Distance(GetActorLocation(), Location);
	TimeToTarget = Distance / ProjectileSpeed;

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location));
	
	ImpactLocation = Location;
	ImpactRotation = Rotation;
	ImpactEffect = Effect;
	ImpactAudio = Audio;
}

