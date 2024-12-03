// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class GAD222_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UNiagaraComponent* ProjectileEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TimeToTarget{ 10000.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ProjectileSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* ImpactEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ImpactLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator ImpactRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* ImpactAudio;

	UFUNCTION()
	void SpawnImpact();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Initilize(float Speed, FVector Location, FRotator Rotation, UNiagaraSystem* Effect, USoundBase* Audio);

};
