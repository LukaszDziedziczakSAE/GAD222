// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EBodyPart.h"
#include "EZombieBehaviour.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WalkingSpeed{100.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RunningSpeed{ 600.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OneLegWalkingSpeed{ 50.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CrawlingSpeed{ 50.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* LeftHandAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* RightHandAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* LeftHandSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* RightHandSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackRate{ 1.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UZombieHealth* ZombieHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAlive{ true };

	UFUNCTION()
	void AttackComplete();

	UFUNCTION()
	virtual void OnOverlapLeftHandBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapRightHandBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HandAttackPower{ 60.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* DeathMontage;

	UFUNCTION()
	void DeathComplete();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UNiagaraComponent* BurningFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* ZombieIdleAudio;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* Shirt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* Pants;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* Hair;

	UFUNCTION(BlueprintCallable)
	void DetachMesh(USkeletalMeshComponent* BodyPart);

	UFUNCTION(BlueprintCallable)
	void DetachBodyPart(TEnumAsByte<EBodyPart> BodyPart);

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EZombieLocomotion> GetZombieLocomotion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasHead{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasLeftArm{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasRightArm{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasLeftLeg{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasRightLeg{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EZombieBehaviour> Behaviour;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bLeftHandAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bRightHandAttacking;

	UFUNCTION(BlueprintCallable)
	void SetMovementSpeed();

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintPure)
	bool IsAlive() { return bIsAlive; }

	UFUNCTION(BlueprintCallable)
	void Death();

	UFUNCTION(BlueprintCallable)
	void InflictDamage(float Amount, USkeletalMeshComponent* BodyPart = nullptr);

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EBodyPart> BodyPartFromMesh(USkeletalMeshComponent* BodyPart);

	UFUNCTION(BlueprintCallable)
	void StartBurning();
};
