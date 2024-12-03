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
#include "ZombieGameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ZombieGame_PlayerController.h"

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

	Top = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Top"));
	Top->SetupAttachment(GetMesh());
	Top->SetLeaderPoseComponent(GetMesh());

	Bottom = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bottom"));
	Bottom->SetupAttachment(GetMesh());
	Bottom->SetLeaderPoseComponent(GetMesh());

	Shoes = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoes"));
	Shoes->SetupAttachment(GetMesh());
	Shoes->SetLeaderPoseComponent(GetMesh());

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->SetLeaderPoseComponent(GetMesh());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(GetMesh());
	Arms->SetLeaderPoseComponent(GetMesh());

	NeckBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Neck Bleed"));
	NeckBleed->SetupAttachment(GetMesh(), TEXT("clavicle_r"));
	NeckBleed->bAutoActivate = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr) HUD = Cast<AZombieStoryHUD>(PlayerController->GetHUD());

	SetMovementSpeed();

	UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance != nullptr) GameInstance->PlayerCharacterStart(this);
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

	//GetMesh()->Stop();

	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));

	PlayerDeathEvent.Broadcast();
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
		FVector CharacterPoint = GetActorLocation() + FVector{0,0,65};
		FRotator ImpactRotation = UKismetMathLibrary::FindLookAtRotation(CharacterPoint, HitResult.ImpactPoint);

		FRotator Difference = ImpactRotation - GetActorRotation();

		UE_LOG(LogTemp, Warning, TEXT("ImpactRotation: %s"), *ImpactRotation.ToString());
		FVector2D ReturnValue = FVector2D{ Difference.Yaw, Difference.Pitch };


		//UE_LOG(LogTemp, Warning, TEXT("Return: %s"), *ReturnValue.ToString());

		return ReturnValue;
	}
	return FVector2D{0.0f, 0.0f};
}

UZombieGameInstance* APlayerCharacter::GetGameInstance()
{
	return Cast<UZombieGameInstance>(GetWorld()->GetGameInstance());
}

void APlayerCharacter::ZombieCQCStart(FVector ZombiePosition)
{
	bZombieCQC = true;
	bCanMove = false;
	FVector Direction = (ZombiePosition - GetActorLocation());
	SetActorRotation((FRotationMatrix::MakeFromX(Direction).ToQuat()), ETeleportType::None);
	CQCDefence = 0;

	AZombieGame_PlayerController* PlayerController = Cast<AZombieGame_PlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->TutorialZombieFight(true);
	}
}

void APlayerCharacter::ZombieTakedown()
{
	bZombieTakedown = true;
	FTimerHandle TakeDownDeathHandle;
	GetWorld()->GetTimerManager().SetTimer(TakeDownDeathHandle, this, &APlayerCharacter::Death, 2.0f, false);
}

void APlayerCharacter::ZombieCQCEnd()
{
	bZombieCQC = false;
	bCanMove = true;
	NeckBleed->Deactivate();

	AZombieGame_PlayerController* PlayerController = Cast<AZombieGame_PlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->TutorialZombieFight(false);
	}
}

void APlayerCharacter::Clothed(bool bIsClothed)
{
	if (bShowClothesOverride)
	{
		GetMesh()->SetSkeletalMesh(BodyClothed);
		Top->SetVisibility(true);
		Bottom->SetVisibility(true);
		Shoes->SetVisibility(true);
		Arms->SetVisibility(true);
		return;
	}

	if (bIsClothed)
	{
		GetMesh()->SetSkeletalMesh(BodyClothed);
		Top->SetVisibility(true);
		Bottom->SetVisibility(true);
		Shoes->SetVisibility(true);
		Arms->SetVisibility(true);
	}
	else
	{
		GetMesh()->SetSkeletalMesh(BodyUnclothed);
		Top->SetVisibility(false);
		Bottom->SetVisibility(false);
		Shoes->SetVisibility(false);
		Arms->SetVisibility(false);
	}

	UZombieGameInstance* GameInstance = Cast<UZombieGameInstance>(GetGameInstance());
	if (GameInstance != nullptr) GameInstance->bHasClothesOn = bIsClothed;
}

void APlayerCharacter::PickedUpItemBroadcast(FString MessageText)
{
	PlayerPickupEvent.Broadcast(MessageText);
}

void APlayerCharacter::StartNeckBleed()
{
	if (NeckBleed != nullptr && !NeckBleed->IsActive())
	{
		NeckBleed->Activate(true);
	}
}

void APlayerCharacter::SaveToGameInstance()
{
	WeaponManagerComponent->Save();

	AZombieGame_PlayerController* PlayerController = Cast<AZombieGame_PlayerController>(GetController());
	if (PlayerController != nullptr) PlayerController->TutorialSave();
}
