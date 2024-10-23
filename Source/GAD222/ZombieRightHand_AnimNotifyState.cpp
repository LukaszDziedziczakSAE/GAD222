// Lukasz Dziedziczak 2024


#include "ZombieRightHand_AnimNotifyState.h"
#include "ZombieCharacter.h"

void UZombieRightHand_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(MeshComp->GetOwner());

	ZombieCharacter->bRightHandAttacking = true;
}

void UZombieRightHand_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(MeshComp->GetOwner());

	ZombieCharacter->bRightHandAttacking = false;
}
