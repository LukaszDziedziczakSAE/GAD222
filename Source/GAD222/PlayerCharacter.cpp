// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponManagerComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "ZombieStoryHUD.h"
#include "PlayerHealth.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Sprint Arm Component"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);

	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("Weapon Manager Component"));
	PlayerInteraction = CreateDefaultSubobject<UPlayerInteraction>(TEXT("Player Interaction"));
	PlayerHealth = CreateDefaultSubobject<UPlayerHealth>(TEXT("Player Health"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr) HUD = Cast<AZombieStoryHUD>(PlayerController->GetHUD());

	SetMovementSpeed();
}

void APlayerCharacter::DeathComplete()
{
	GetMesh()->Stop();

	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::StartAiming()
{
	if (WeaponManagerComponent->CurrentWeapon == nullptr) return;

	bIsAiming = true;
	SpringArm->SetRelativeLocation(FVector(0, 30, 70));
	SpringArm->TargetArmLength = 75.0f;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	SetMovementSpeed();
	OnAimStart.Broadcast();
}

void APlayerCharacter::StopAiming()
{
	SpringArm->SetRelativeLocation(FVector(0, 0, 80));
	SpringArm->TargetArmLength = 250.0f;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bIsAiming = false;
	SetMovementSpeed();
	OnAimStop.Broadcast();
}

void APlayerCharacter::SwitchCamera(AActor* NewViewTarget)
{
	if (bInComputerView) return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr) return;
	FViewTargetTransitionParams ViewTargetTransitionParams;
	ViewTargetTransitionParams.BlendFunction = EViewTargetBlendFunction::VTBlend_EaseInOut;
	ViewTargetTransitionParams.BlendTime = 0.5f;
	PlayerController->SetViewTarget(NewViewTarget, ViewTargetTransitionParams);
	if (HUD != nullptr)
	{
		HUD->RemoveAllFromViewport();

		FTimerHandle CameraSwitchTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(CameraSwitchTimerHandle, HUD, &AZombieStoryHUD::SwitchToComputerView, 0.5f, false);
	}
	bInComputerView = true;
}

void APlayerCharacter::SwitchBackToPlayerCamera()
{
	if (!bInComputerView) return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr) return;
	FViewTargetTransitionParams ViewTargetTransitionParams;
	ViewTargetTransitionParams.BlendFunction = EViewTargetBlendFunction::VTBlend_EaseInOut;
	ViewTargetTransitionParams.BlendTime = 0.5f;
	PlayerController->SetViewTarget(this, ViewTargetTransitionParams);
	if (HUD != nullptr)
	{
		HUD->RemoveAllFromViewport();

		FTimerHandle CameraSwitchTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(CameraSwitchTimerHandle, HUD, &AZombieStoryHUD::SwitchToPlayerView, 0.5f, false);
	}
	bInComputerView = false;
}

void APlayerCharacter::Death()
{
	bIsAlive = false;

	/*float t = PlayAnimMontage(DeathMontage, 2);
	t -= 0.5f;
	FTimerHandle AttackTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &APlayerCharacter::DeathComplete, t, false);*/

	DeathComplete();
}

void APlayerCharacter::InflictDamage(float Amount)
{
	PlayerHealth->TakeHealth(Amount);
}

void APlayerCharacter::SetMovementSpeed()
{
	if (bIsAiming)
	{
		GetCharacterMovement()->MaxWalkSpeed = AimWalkingSpeed;
	}
	else if (WeaponManagerComponent->CurrentWeapon != nullptr)
	{
		if (bIsRunning) GetCharacterMovement()->MaxWalkSpeed = ArmedJoggingSpeed;
		else GetCharacterMovement()->MaxWalkSpeed = ArmedWalkingSpeed;
	}
	else
	{
		if (bIsRunning) GetCharacterMovement()->MaxWalkSpeed = JoggingSpeed;
		else GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
}

void APlayerCharacter::StartRunning()
{
	bIsRunning = true;
	SetMovementSpeed();
}

void APlayerCharacter::StopRunning()
{
	bIsRunning = false;
	SetMovementSpeed();
}

FVector2D APlayerCharacter::AimOffset()
{
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.bTraceIntoSubComponents = true;

	//Re-initialize hit info
	FHitResult HitResult(ForceInit);

	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (PlayerCameraManager->GetActorForwardVector() * 10000);

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,		//result
		Start,	//start
		End, //end
		ECC_GameTraceChannel1, //collision channel (ECC_GameTraceChannel1)
		TraceParams
	))
	{
		FVector CharacterPoint = GetActorLocation() + FVector{0,0,150};
		FRotator ImapctRotation = UKismetMathLibrary::FindLookAtRotation(CharacterPoint, HitResult.ImpactPoint);

		return FVector2D{ ImapctRotation.Pitch, ImapctRotation.Yaw };
	}
	return FVector2D();
}
