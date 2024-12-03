// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TutorialComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTutorialMessage, FString, Message);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD222_API UTutorialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget_Tutorial* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LookThreshhold{ 30.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Looked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasLookedAround;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasMoved;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasSprinted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasEquipedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasReloaded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasAimed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasFiredWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasFoughtZombie;

	UFUNCTION(BlueprintCallable)
	void ShowLookTutorial();

	UFUNCTION(BlueprintCallable)
	void Save();

	UFUNCTION(BlueprintCallable)
	void Load();
};
