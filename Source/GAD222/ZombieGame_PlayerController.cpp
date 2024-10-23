// Lukasz Dziedziczak 2024


#include "ZombieGame_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "WeaponManagerComponent.h"
#include "PlayerInteraction.h"
#include "ZombieStoryHUD.h"

void AZombieGame_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieGame_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacter>(aPawn);
}

void AZombieGame_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem != nullptr && InputMapping != nullptr)
	{
		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}
	else if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Subsystem Referance"), *GetName());
		return;
	}
	else if (InputMapping == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Mapping Referance"), *GetName());
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (Input != nullptr)
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AZombieGame_PlayerController::Move);
		Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AZombieGame_PlayerController::Look);
		Input->BindAction(IA_Aim, ETriggerEvent::Started, this, &AZombieGame_PlayerController::AimStart);
		Input->BindAction(IA_Aim, ETriggerEvent::Completed, this, &AZombieGame_PlayerController::AimEnd);
		Input->BindAction(IA_Fire, ETriggerEvent::Started, this, &AZombieGame_PlayerController::PullTrigger);
		Input->BindAction(IA_Fire, ETriggerEvent::Completed, this, &AZombieGame_PlayerController::ReleaseTrigger);
		Input->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AZombieGame_PlayerController::Interact);
		Input->BindAction(IA_WeaponSelect, ETriggerEvent::Completed, this, &AZombieGame_PlayerController::WeaponSelect);
		Input->BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AZombieGame_PlayerController::PauseGame);
		
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void AZombieGame_PlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;

	FRotator CharacterRotation = PlayerCharacter->GetControlRotation();

	PlayerCharacter->AddMovementInput(
		UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
		Value.Get<FVector2D>().Y);

	PlayerCharacter->AddMovementInput(
		UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
		Value.Get<FVector2D>().X);
}

void AZombieGame_PlayerController::Look(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;

	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(-1 * Value.Get<FVector2D>().Y);
}

void AZombieGame_PlayerController::AimStart(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->StartAiming();
}

void AZombieGame_PlayerController::AimEnd(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->StopAiming();
}

void AZombieGame_PlayerController::PullTrigger(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;

	if (PlayerCharacter->IsAiming())
	{
		PlayerCharacter->WeaponManagerComponent->PullTrigger();
	}
}

void AZombieGame_PlayerController::ReleaseTrigger(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;

	if (PlayerCharacter->IsAiming())
	{
		PlayerCharacter->WeaponManagerComponent->ReleaseTrigger();
	}
}

void AZombieGame_PlayerController::WeaponSelect(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->WeaponManagerComponent->EquipWeapon();
}

void AZombieGame_PlayerController::PauseGame(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;

	if (bGamePaused)
	{
		Cast<AZombieStoryHUD>(GetHUD())->GameUnpaused();
	}
	else
	{
		Cast<AZombieStoryHUD>(GetHUD())->GamePaused();
	}
}

void AZombieGame_PlayerController::Interact(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->PlayerInteraction->Interact();
}
