// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Door.h"
#include "ZombieGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API UZombieGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Checkpoint{ 0 };

	UFUNCTION()
	void AddPickup(FString Name);

	UFUNCTION(BlueprintCallable)
	void PlayerCharacterStart(class APlayerCharacter* PlayerCharacter);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int KeycardLevel;

	UFUNCTION(BlueprintCallable)
	void Reset();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int PistolAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int PistolAmmoStorage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bMaleCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bHasClothesOn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TEnumAsByte<EDoorState> DoorState{ DoorClosed };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasLookedAround;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasMoved;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasSprinted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasEquipedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasReloaded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasAimed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasFiredWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasFoughtZombie;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> Pickups;
};
