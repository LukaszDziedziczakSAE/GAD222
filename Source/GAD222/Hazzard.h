// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hazzard.generated.h"

UCLASS()
class GAD222_API AHazzard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazzard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHazzardIsActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UParticleSystemComponent*> Effects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ACharacter*> CharactersInHazzard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TurnOnHazzard();

	UFUNCTION(BlueprintCallable)
	void TurnOffHazzard();

	UFUNCTION(BlueprintCallable)
	void ToggleHazzard();

	UFUNCTION(BlueprintPure)
	bool IsActive() { return bHazzardIsActive; }
};
