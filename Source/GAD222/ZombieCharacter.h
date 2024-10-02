// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EBodyPart.h"
#include "ZombieCharacter.generated.h"

UENUM(BlueprintType)
enum EZombieLocomotion
{
	BothLegs UMETA(DisplayName = "Both Legs"),
	LeftLegOnly UMETA(DisplayName = "Left Leg Only"),
	RightLegOnly UMETA(DisplayName = "Right Leg Only"),
	NoLegs UMETA(DisplayName = "No Legs")
};

UCLASS()
class GAD222_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* Head;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* LeftArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* RightArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* LeftLeg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* RightLeg;

	UFUNCTION(BlueprintCallable)
	void DetachBodyPart(USkeletalMeshComponent* BodyPart);

	UFUNCTION(BlueprintCallable)
	void BodyPartHit(USkeletalMeshComponent* BodyPart);

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EZombieLocomotion> GetZombieLocomotion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasLeftLeg{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasRightLeg{ true };
};
