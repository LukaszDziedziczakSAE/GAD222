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
	class UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Aim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Fire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_WeaponSelect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Pause;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Reload;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bGamePaused;

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

	UFUNCTION()
	void PauseGame(const FInputActionValue& Value);
};
