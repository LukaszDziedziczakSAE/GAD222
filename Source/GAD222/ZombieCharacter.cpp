// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void AZombieCharacter::DetachBodyPart(USkeletalMeshComponent* BodyPart)
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

void AZombieCharacter::BodyPartHit(USkeletalMeshComponent* BodyPart)
{
	if (BodyPart->GetName() == GetMesh()->GetName()) return;

	DetachBodyPart(BodyPart);

	if (BodyPart == LeftLeg) bHasLeftLeg = false;
	else if (BodyPart == RightLeg) bHasRightLeg = false;
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

