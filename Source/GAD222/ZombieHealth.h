// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EBodyPart.h"
#include "ZombieHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD222_API UZombieHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZombieHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AZombieCharacter* ZombieCharacter;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth{ 50.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxLegHealth{ 20.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LeftLegHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float RightLegHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxArmHealth{ 30.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LeftArmHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float RightArmHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHeadHealth{ 30.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HeadHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TakeHealth(float Amount, EBodyPart BodyPart);
};
