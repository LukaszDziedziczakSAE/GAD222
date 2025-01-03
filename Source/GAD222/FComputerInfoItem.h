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
	FText Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> TextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMediaSource* Media;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ADoor* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMusicTrigger* MusicTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Checkpoint{ -1 };
};