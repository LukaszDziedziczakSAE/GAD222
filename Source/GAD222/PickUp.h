// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"


UENUM(BlueprintType)
enum EPickUpType
{
	NoPickUp UMETA(DisplayName = "No Pick Up"),
	PistolPickup UMETA(DisplayName = "Pistol"),
	PistolAmmoPickup UMETA(DisplayName = "Pistol Ammo"),
	ClothingPickup UMETA(DisplayName = "Clothing"),
	Keycard1Pickup UMETA(DisplayName = "Keycard Level 1"),
	Keycard2Pickup UMETA(DisplayName = "Keycard Level 2"),
	Keycard3Pickup UMETA(DisplayName = "Keycard Level 3")
};

UCLASS()
class GAD222_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EPickUpType> PickUpType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Amount;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void PickUp(class APlayerCharacter* PlayerCharacter);

	UFUNCTION()
	void PickupPistol(APlayerCharacter* PlayerCharacter);

	UFUNCTION()
	void PickupPistolAmmo(APlayerCharacter* PlayerCharacter);

	UFUNCTION()
	void PickupKeycard(APlayerCharacter* PlayerCharacter, int KeycardLevel);
};
