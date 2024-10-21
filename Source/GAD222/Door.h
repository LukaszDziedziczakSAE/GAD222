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
	DoorClosing UMETA(DisplayName = "Closing")
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* OpenEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* OpeningSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* ClosingSound;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpeningTime{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector OpenPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ClosedPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector OpenPosition2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ClosedPosition2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLockOnClose;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bManualOverride;

	UFUNCTION()
	void OpeningTick();

	UFUNCTION()
	void ClosingTick();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ActionTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsLocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EDoorState> DoorState;

	UFUNCTION(BlueprintCallable)
	void OpenDoor();

	UFUNCTION(BlueprintCallable)
	void CloseDoor();
};
