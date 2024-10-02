// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"

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
	BodyPart->Stop();
	BodyPart->DetachFromParent(true);
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

