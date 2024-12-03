// Lukasz Dziedziczak 2024


#include "ZombieGame_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "WeaponManagerComponent.h"
#include "PlayerInteraction.h"
#include "ZombieStoryHUD.h"
#include "TutorialComponent.h"
#include "UserWidget_Tutorial.h"

AZombieGame_PlayerController::AZombieGame_PlayerController()
{
	TutorialComponent = CreateDefaultSubobject<UTutorialComponent>(TEXT("Tutorial Component"));
}

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
		Input->BindAction(IA_Pause, ETriggerEvent::Started, this, &AZombieGame_PlayerController::PauseGame);
		Input->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &AZombieGame_PlayerController::Reload);
		Input->BindAction(IA_Run, ETriggerEvent::Started, this, &AZombieGame_PlayerController::StartRunning);
		Input->BindAction(IA_Run, ETriggerEvent::Completed, this, &AZombieGame_PlayerController::StopRunning);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void AZombieGame_PlayerController::Move(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive() || !PlayerCharacter->CanMove()) return;

	FRotator CharacterRotation = PlayerCharacter->GetControlRotation();

	PlayerCharacter->AddMovementInput(
		UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
		Value.Get<FVector2D>().Y);

	PlayerCharacter->AddMovementInput(
		UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
		Value.Get<FVector2D>().X);

	if (!TutorialComponent->bHasMoved && Value.Get<FVector2D>().Length() > 0.0f)
	{
		TutorialComponent->bHasMoved = true;
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideMoveTutorialText();

		if (!TutorialComponent->bHasSprinted)
		{
			if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->ShowSprintTutorialText();
		}
	}
}

void AZombieGame_PlayerController::Look(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr) return;

	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(-1 * Value.Get<FVector2D>().Y);

	if (!TutorialComponent->bHasLookedAround)
	{
		float YStep = Value.Get<FVector2D>().Y;
		if (YStep < 0) YStep *= -1;
		float XStep = Value.Get<FVector2D>().X;
		if (XStep < 0) XStep *= -1;

		TutorialComponent->Looked += YStep;
		TutorialComponent->Looked += XStep;

		if (TutorialComponent->Looked >= TutorialComponent->LookThreshhold)
		{
			TutorialComponent->bHasLookedAround = true;
			if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideLookTutorialText();

			if (!TutorialComponent->bHasMoved)
			{
				if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->ShowMoveTutorialText();
			}
		}
	}
}

void AZombieGame_PlayerController::AimStart(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive() || !PlayerCharacter->CanMove() || PlayerCharacter->WeaponManagerComponent->CurrentWeapon == nullptr) return;

	PlayerCharacter->StartAiming();

	if (!TutorialComponent->bHasAimed)
	{
		TutorialComponent->bHasAimed = true;
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideAimingTextTutorial();
	}

	if (!TutorialComponent->bHasFiredWeapon)
	{
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->ShowFiringTextTutorial();
	}
}

void AZombieGame_PlayerController::AimEnd(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr || PlayerCharacter->WeaponManagerComponent->CurrentWeapon == nullptr) return;
	PlayerCharacter->StopAiming();
}

void AZombieGame_PlayerController::PullTrigger(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive()) return;

	if (PlayerCharacter->IsAiming())
	{
		PlayerCharacter->WeaponManagerComponent->PullTrigger();

		if (!TutorialComponent->bHasFiredWeapon)
		{
			TutorialComponent->bHasFiredWeapon = true;
			if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideFiringTextTutorial();
		}
	}

	if (PlayerCharacter->InZombieCQC())
	{
		PlayerCharacter->CQCDefence++;

		if (!TutorialComponent->bHasFoughtZombie)
		{
			TutorialComponent->bHasFoughtZombie = true;
			TutorialComponent->Widget->HideZombieStrugleTextTutorial();
		}
	}
}

void AZombieGame_PlayerController::ReleaseTrigger(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr) return;

	if (PlayerCharacter->IsAiming())
	{
		PlayerCharacter->WeaponManagerComponent->ReleaseTrigger();
	}
}

void AZombieGame_PlayerController::WeaponSelect(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive() || !PlayerCharacter->CanMove()) return;
	PlayerCharacter->WeaponManagerComponent->EquipWeapon();

}

void AZombieGame_PlayerController::PauseGame(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr) return;
	

	if (bGamePaused)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unpause Game"));
		bGamePaused = false;
		Cast<AZombieStoryHUD>(GetHUD())->GameUnpaused();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pause Game"));
		bGamePaused = true;
		Cast<AZombieStoryHUD>(GetHUD())->GamePaused();
	}
}

void AZombieGame_PlayerController::TutorialSave()
{
	TutorialComponent->Save();
}

void AZombieGame_PlayerController::TutorialWeaponPickedUp()
{
	if (!TutorialComponent->bHasEquipedWeapon)
	{
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->ShowEquipTutorialText();
	}
}

void AZombieGame_PlayerController::TutorialWeaponEquiped(bool bHasAmmo)
{
	if (!TutorialComponent->bHasEquipedWeapon)
	{
		TutorialComponent->bHasEquipedWeapon = true;
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideEquipTutorialText();
	}

	if (!TutorialComponent->bHasAimed)
	{
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->ShowAimingTextTutorial();
	}

	if (bHasAmmo && !TutorialComponent->bHasReloaded)
	{
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->ShowReloadTutorialText();
	}
}

void AZombieGame_PlayerController::TutorialWeaponUnequiped()
{
	if (!TutorialComponent->bHasAimed)
	{
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideAimingTextTutorial();
	}

	if (!TutorialComponent->bHasReloaded)
	{
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideAimingTextTutorial();
	}
}

void AZombieGame_PlayerController::TutorialWeaponReloaded()
{
	if (!TutorialComponent->bHasReloaded)
	{
		TutorialComponent->bHasReloaded = true;
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideReloadTutorialText();
	}
}

void AZombieGame_PlayerController::TutorialZombieFight(bool bStarted)
{
	if (TutorialComponent->Widget == nullptr) return;

	if (!TutorialComponent->bHasFoughtZombie)
	{
		if (bStarted) TutorialComponent->Widget->ShowZombieStrugleTextTutorial();
		else TutorialComponent->Widget->HideZombieStrugleTextTutorial();
	}
}

void AZombieGame_PlayerController::Interact(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive() || !PlayerCharacter->CanMove()) return;
	PlayerCharacter->PlayerInteraction->Interact();
}

void AZombieGame_PlayerController::Reload(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive() || !PlayerCharacter->CanMove()) return;
	PlayerCharacter->WeaponManagerComponent->ReloadCurrentWeapon();
}

void AZombieGame_PlayerController::StartRunning(const FInputActionValue& Value)
{
	if (bDisableControl) return;
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsAlive() || !PlayerCharacter->CanMove()) return;
	PlayerCharacter->StartRunning();

	if (!TutorialComponent->bHasSprinted)
	{
		TutorialComponent->bHasSprinted = true;
		if (TutorialComponent->Widget != nullptr) TutorialComponent->Widget->HideSprintTutorialText();
	}
}

void AZombieGame_PlayerController::StopRunning(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->StopRunning();
}
