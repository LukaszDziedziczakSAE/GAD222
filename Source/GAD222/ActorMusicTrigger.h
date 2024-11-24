// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MusicTrigger.h"
#include "ActorMusicTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD222_API UActorMusicTrigger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorMusicTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AZombieCharacter* Zombie;

	UFUNCTION()
	void OnZombieDeath();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETriggerAction> Action1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETriggerAction> Action2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETriggerAction> Action3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETriggerAction> Action4;

	UFUNCTION()
	void RunAction(TEnumAsByte<ETriggerAction> Action);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMusic* Music;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
