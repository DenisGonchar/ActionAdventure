#pragma once

#include "CoreMinimal.h"

#include "AAPersistentModelSaveSlot.generated.h"

USTRUCT(BlueprintType)
struct FAAPersistentModelSaveSlot
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SlotName;
	
};