// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EWeaponType.h"
#include "Weapon.generated.h"

UCLASS()
class GAD222_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EWeaponType> WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USoundCue* FireSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UNiagaraSystem* FireEffectMuzzle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TraceLength{ 1000.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UNiagaraSystem* Impact;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	TEnumAsByte<EWeaponType> GetWeaponType() { return WeaponType; }

	UFUNCTION()
	void Fire();
};
