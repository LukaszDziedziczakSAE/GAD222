// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EWeaponType.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAimStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAimStopDelegate);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* DeathMontage;

	UFUNCTION()
	void DeathComplete();

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
};
