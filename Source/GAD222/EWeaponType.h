// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EWeaponType
{
	Hands UMETA(DisplayName = "Hands"),
	Pistol UMETA(DisplayName = "Pistol"),
	Rifle UMETA(DisplayName = "Rifle"),
	Shotgun UMETA(DisplayName = "Shotgun")
};
