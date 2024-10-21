// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "FComputerInfoItem.generated.h"

USTRUCT(BlueprintType)
struct GAD222_API FComputerInfoItem
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Label;
};