// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FWeaponData.h"
#include "WeaponManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD222_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeaponData> Weapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerCharacter* PlayerCharacter;

	UFUNCTION()
	void ReloadAnimationComplete();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class AWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HasPistol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PistolAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PistolAmmoStorage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsReloading; 

	UFUNCTION(BlueprintCallable)
	void EquipWeapon();

	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();

	UFUNCTION()
	void SpawnWeapon();

	UFUNCTION()
	void DespawnWeapon();

	UFUNCTION(BlueprintCallable)
	void PullTrigger();

	UFUNCTION(BlueprintCallable)
	void ReleaseTrigger();

	UFUNCTION(BlueprintCallable)
	void ReloadCurrentWeapon();
};
