// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableHazzardControl.generated.h"

UENUM(BlueprintType)
enum EHazzardControlState
{
	Open,
	Openning,
	Closing,
	Closed
};

UCLASS()
class GAD222_API AInteractableHazzardControl : public AInteractable
{
	GENERATED_BODY()

public:
	AInteractableHazzardControl();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AHazzard* Hazzard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EHazzardControlState> HazzardControlState{ Open };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Valve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* ValvePivot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ClosedAngle{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float OpenAngle{ 180.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TransitionTime{ 2.5f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentTransitionTime;

	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;
	
};
