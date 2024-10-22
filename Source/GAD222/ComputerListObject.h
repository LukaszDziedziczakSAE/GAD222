// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ComputerListObject.generated.h"

/**
 * 
 */
UCLASS()
class GAD222_API UComputerListObject : public UObject
{
	GENERATED_BODY()

public:
	struct FComputerInfoItem* ComputerInfoItem;
	
};
