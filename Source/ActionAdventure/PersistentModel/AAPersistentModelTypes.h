#pragma once

#include "CoreMinimal.h"

#include "AAPersistentModelTypes.generated.h"

USTRUCT(BlueprintType)
struct FAAPersistentModelId
{
	GENERATED_BODY()
public:
	bool operator ==(const FAAPersistentModelId& Other) const
	{
		return Id == Other.Id;
	}

	bool IsValid() const
	{
		return Id.IsValid();
	}

	FString ToString() const
	{
		return Id.ToString();
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid Id;
	
};