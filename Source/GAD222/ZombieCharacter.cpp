// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "ZombieHealth.h"
#include "ZombieAIController.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(GetMesh());

	LeftArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Arm"));
	LeftArm->SetupAttachment(GetMesh());

	RightArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Arm"));
	RightArm->SetupAttachment(GetMesh());

	LeftLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Leg"));
	LeftLeg->SetupAttachment(GetMesh());

	RightLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Leg"));
	RightLeg->SetupAttachment(GetMesh());

	Shirt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shirt"));
	Shirt->SetupAttachment(GetMesh());

	Pants = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pants"));
	Pants->SetupAttachment(GetMesh());

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	Hair->SetupAttachment(Head);

	LeftHandSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Left Hand Sphere"));
	LeftHandSphere->SetupAttachment(GetMesh(), TEXT("LeftHand"));
	LeftHandSphere->SetRelativeLocation(FVector{ 15.0f, 0,0 });
	LeftHandSphere->SetSphereRadius(15.0f);
	LeftHandSphere->OnComponentBeginOverlap.AddDynamic(this, &AZombieCharacter::OnOverlapLeftHandBegin);

	RightHandSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Right Hand Sphere"));
	RightHandSphere->SetupAttachment(GetMesh(), TEXT("RightHand"));
	RightHandSphere->SetRelativeLocation(FVector{ -15.0f, 0,0 });
	RightHandSphere->SetSphereRadius(15.0f);
	RightHandSphere->OnComponentBeginOverlap.AddDynamic(this, &AZombieCharacter::OnOverlapRightHandBegin);

	ZombieHealth = CreateDefaultSubobject<UZombieHealth>(TEXT("Zombie Health"));

	BurningFire = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Burning Fire"));
	BurningFire->SetupAttachment(GetRootComponent());
	BurningFire->SetRelativeLocation(FVector{0,0,-84.0f});
	BurningFire->bAutoActivate = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(GetRootComponent());
	AudioComponent->SetRelativeLocation(FVector{0,0,60});
}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZombieCharacter::AttackComplete()
{
	bIsAttacking = false;
}

void AZombieCharacter::OnOverlapLeftHandBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bLeftHandAttacking) return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Player"));

		PlayerCharacter->InflictDamage(HandAttackPower);
	}
}

void AZombieCharacter::OnOverlapRightHandBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bRightHandAttacking) return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Player"));

		PlayerCharacter->InflictDamage(HandAttackPower);
	}
}

void AZombieCharacter::DeathComplete()
{
	GetMesh()->Stop();

	/*GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));*/

}

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombieCharacter::DetachMesh(USkeletalMeshComponent* BodyPart)
{
	if (BodyPart == Head)
	{
		Hair->Stop();
		//Hair->DetachFromParent(true);
		Hair->SetSimulatePhysics(true);
	}

	BodyPart->Stop();
	BodyPart->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	BodyPart->SetSimulatePhysics(true);
}

void AZombieCharacter::DetachBodyPart(TEnumAsByte<EBodyPart> BodyPart)
{
	switch (BodyPart)
	{
	case EBodyPart::Head:
		DetachMesh(Head);
		bHasHead = false;
		break;

	case EBodyPart::LeftArm:
		DetachMesh(LeftArm);
		bHasLeftArm = false;
		break;

	case EBodyPart::RightArm:
		DetachMesh(RightArm);
		bHasRightArm = false;
		break;

	case EBodyPart::Leftleg:
		DetachMesh(LeftLeg);
		bHasLeftLeg = false;
		break;

	case EBodyPart::RightLeg:
		DetachMesh(RightLeg);
		bHasRightLeg = false;
		break;
	}
}

TEnumAsByte<EZombieLocomotion> AZombieCharacter::GetZombieLocomotion()
{
	if (bHasLeftLeg && bHasRightLeg) return EZombieLocomotion::BothLegs;
	else if (bHasLeftLeg) return EZombieLocomotion::LeftLegOnly;
	else if (bHasRightLeg) return EZombieLocomotion::RightLegOnly;
	else return EZombieLocomotion::NoLegs;
}

void AZombieCharacter::SetMovementSpeed()
{
	if (bHasLeftLeg && bHasRightLeg) GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	else if (bHasLeftLeg) GetCharacterMovement()->MaxWalkSpeed = OneLegWalkingSpeed;
	else if (bHasRightLeg) GetCharacterMovement()->MaxWalkSpeed = OneLegWalkingSpeed;
	else GetCharacterMovement()->MaxWalkSpeed = CrawlingSpeed;
}

void AZombieCharacter::Attack()
{
	if (bIsAttacking) return;
	UE_LOG(LogTemp, Warning, TEXT("%s attacking"), *GetName());
	bIsAttacking = true;

	bool RandomBool = UKismetMathLibrary::RandomBool();
	float t;
	if (RandomBool)
	{
		t = PlayAnimMontage(LeftHandAttack, AttackRate);
	}
	else
	{
		t = PlayAnimMontage(RightHandAttack, AttackRate);
	}
	FTimerHandle AttackTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AZombieCharacter::AttackComplete, t, false);

}

void AZombieCharacter::Death()
{
	bIsAlive = false;

	AZombieAIController* AI = Cast<AZombieAIController>(GetController());
	if (AI != nullptr) AI->StopBehaviourTree();

	/*float t = PlayAnimMontage(DeathMontage, 2);
	t -= 0.5f;
	FTimerHandle AttackTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AZombieCharacter::DeathComplete, t, false);*/

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	ZombieDeathEvent.Broadcast();
}

void AZombieCharacter::InflictDamage(float Amount, USkeletalMeshComponent* BodyPart)
{
	ZombieHealth->TakeHealth(Amount, BodyPartFromMesh(BodyPart));
}

TEnumAsByte<EBodyPart> AZombieCharacter::BodyPartFromMesh(USkeletalMeshComponent* BodyPart)
{
	if (BodyPart == Head) return EBodyPart::Head;
	else if (BodyPart == LeftArm) return EBodyPart::LeftArm;
	else if (BodyPart == RightArm) return EBodyPart::RightArm;
	else if (BodyPart == LeftLeg) return EBodyPart::Leftleg;
	else if (BodyPart == RightLeg) return EBodyPart::RightLeg;
	else return EBodyPart::Torso;
}

void AZombieCharacter::StartBurning()
{
	if (BurningFire->IsActive()) return;

	BurningFire->Activate();
}

