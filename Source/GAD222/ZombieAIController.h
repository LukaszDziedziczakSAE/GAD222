// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"


UCLASS()
class GAD222_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieAIController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable)
	void StopBehaviourTree();
};
