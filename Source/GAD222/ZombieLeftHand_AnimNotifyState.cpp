// Lukasz Dziedziczak 2024


#include "ZombieLeftHand_AnimNotifyState.h"
#include "ZombieCharacter.h"

void UZombieLeftHand_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(MeshComp->GetOwner());

	ZombieCharacter->bLeftHandAttacking = true;
}

void UZombieLeftHand_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(MeshComp->GetOwner());

	ZombieCharacter->bLeftHandAttacking = false;
}
