// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum EDoorState
{
	DoorOpen UMETA(DisplayName = "Open"),
	DoorClosed UMETA(DisplayName = "Closed"),
	DoorOpening UMETA(DisplayName = "Opening"),
	DoorCloseing UMETA(DisplayName = "Closeing")
};

UCLASS()
class GAD222_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpeningTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector OpenPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ClosedPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsLocked;

};
