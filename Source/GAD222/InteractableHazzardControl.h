// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableHazzardControl.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API AInteractableHazzardControl : public AInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AHazzard* Hazzard;

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;
	
};
