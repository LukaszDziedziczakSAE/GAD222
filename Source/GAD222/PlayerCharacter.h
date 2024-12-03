// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EWeaponType.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAimStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAimStopDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerPickup, FString, PickupText);

UCLASS()
class GAD222_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Top;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Shoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Hair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Arms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* BodyClothed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* BodyUnclothed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EWeaponType> CurrentWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AZombieStoryHUD* HUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UPlayerHealth* PlayerHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAlive{ true };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanMove{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WalkingSpeed{ 200.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float JoggingSpeed{ 400.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ArmedWalkingSpeed{ 200.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ArmedJoggingSpeed{ 400.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AimWalkingSpeed{ 150.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bZombieCQC{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bZombieTakedown{ false };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int CQCDefenceThreshhold{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShowClothesOverride;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraComponent* NeckBleed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float NormalArmLength{ 150.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AimingArmLength{ 70.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ZombieStrugleArmLength{ 250.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector AimingArmOffset{ 0, 30, 70 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector NormalArmOffset{ 0, 0, 55 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ZombieStrugleOffset{ 0, 0, 100 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraTransitionTime{ 0.4 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CameraTransitionCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TargetCameraOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TargetArmOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LastCameraOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LastArmOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AimingOffsetMultiplier{ 1.25f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CharacterPointHeightOffset{ 70 };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void StartAiming();

	UFUNCTION(BlueprintCallable)
	void StopAiming();

	UPROPERTY(BlueprintAssignable)
	FOnAimStartDelegate OnAimStart;

	UPROPERTY(BlueprintAssignable)
	FOnAimStopDelegate OnAimStop;

	UFUNCTION()
	UCameraComponent* GetCamera() { return Camera; }

	UFUNCTION()
	bool IsAiming() { return bIsAiming; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponManagerComponent* WeaponManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerInteraction* PlayerInteraction;

	UFUNCTION(BlueprintCallable)
	void SwitchCamera(AActor* NewViewTarget);

	UFUNCTION(BlueprintCallable)
	void SwitchBackToPlayerCamera();

	UPROPERTY()
	bool bInComputerView;

	UFUNCTION(BlueprintPure)
	bool IsAlive() { return bIsAlive; }

	UFUNCTION(BlueprintPure)
	bool CanMove() { return bCanMove; }

	UFUNCTION(BlueprintPure)
	bool InZombieCQC() { return bZombieCQC; }

	UFUNCTION(BlueprintPure)
	bool CQCDefenceSucess(){ return CQCDefence >= CQCDefenceThreshhold; }

	UFUNCTION(BlueprintCallable)
	void Death();

	UFUNCTION(BlueprintCallable)
	void InflictDamage(float Amount);

	UFUNCTION(BlueprintAuthorityOnly)
	void SetMovementSpeed();

	UFUNCTION(BlueprintCallable)
	void StartRunning();

	UFUNCTION(BlueprintCallable)
	void StopRunning();

	UFUNCTION(BlueprintCallable)
	FVector2D AimOffset();

	UPROPERTY(BlueprintAssignable)
	FPlayerDeath PlayerDeathEvent;

	UFUNCTION(BlueprintPure)
	class UZombieGameInstance* GetGameInstance();

	UFUNCTION(BlueprintCallable)
	void ZombieCQCStart(FVector ZombiePosition);

	UFUNCTION(BlueprintCallable)
	void ZombieTakedown();

	UFUNCTION(BlueprintCallable)
	void ZombieCQCEnd();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CQCDefence;

	UFUNCTION(BlueprintCallable)
	void Clothed(bool bIsClothed);

	UPROPERTY(BlueprintAssignable)
	FPlayerPickup PlayerPickupEvent;

	UFUNCTION(BlueprintCallable)
	void PickedUpItemBroadcast(FString MessageText);

	UFUNCTION(BlueprintCallable)
	void StartNeckBleed();

	UFUNCTION(BlueprintCallable)
	void SaveToGameInstance();
};
