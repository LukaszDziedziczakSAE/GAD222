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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PistolAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PistolAmmoStorage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bMaleCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bHasClothesOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDoorState> DoorState{ DoorClosed };
	
protected:
	UPROPERTY()
	TArray<FString> Pickups;
};
