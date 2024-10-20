// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD222_API UPlayerInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AInteractable* Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int KeycardLevel;

	UFUNCTION(BlueprintCallable)
	void Interact();
};
