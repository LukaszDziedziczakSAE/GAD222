// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RelativeRotation;
};
