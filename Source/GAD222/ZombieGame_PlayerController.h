// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZombieGame_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API AZombieGame_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AZombieGame_PlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Aim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Fire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_WeaponSelect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Pause;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Reload;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bGamePaused;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UTutorialComponent* TutorialComponent;

	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void AimStart(const FInputActionValue& Value);

	UFUNCTION()
	void AimEnd(const FInputActionValue& Value);

	UFUNCTION()
	void PullTrigger(const FInputActionValue& Value);

	UFUNCTION()
	void ReleaseTrigger(const FInputActionValue& Value);

	UFUNCTION()
	void WeaponSelect(const FInputActionValue& Value);

	UFUNCTION()
	void Interact(const FInputActionValue& Value);

	UFUNCTION()
	void Reload(const FInputActionValue& Value);

	UFUNCTION()
	void StartRunning(const FInputActionValue& Value);

	UFUNCTION()
	void StopRunning(const FInputActionValue& Value);

public:

	UFUNCTION(BlueprintCallable)
	void PauseGame(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDisableControl;

	UFUNCTION(BlueprintCallable)
	void TutorialSave();

	UFUNCTION(BlueprintCallable)
	void TutorialWeaponPickedUp();

	UFUNCTION(BlueprintCallable)
	void TutorialWeaponEquiped(bool bHasAmmo);

	UFUNCTION(BlueprintCallable)
	void TutorialWeaponUnequiped();

	UFUNCTION(BlueprintCallable)
	void TutorialWeaponReloaded();

	UFUNCTION(BlueprintCallable)
	void TutorialZombieFight(bool bStarted);
};
