// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicTrigger.generated.h"

UENUM(BlueprintType)
enum ETriggerAction
{
	NoAction,
	FadeIn_Percussive,
	FadeOut_Percussive,
	FadeIn_Atmospheric,
	FadeOut_Atmospheric,
	FadeIn_Piano,
	FadeOut_Piano,
	FadeIn_Bongos,
	FadeOut_Bongos,
	FadeIn_Strings,
	FadeOut_Strings,
	FadeIn_SquareWave,
	FadeOut_SquareWave
};

UCLASS()
class GAD222_API AMusicTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* Trigger;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bActive{ true };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Activate();

};
