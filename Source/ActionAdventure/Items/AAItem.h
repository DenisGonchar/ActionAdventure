#pragma once

#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AAItem.generated.h"

class UTexture2D;

UCLASS(BlueprintType, Blueprintable, Abstract)
class AAAItem : public AActor
{
	GENERATED_BODY()

public:
	virtual void UseFromInventory();

	void PersistentModelSpawn(struct FAAPMStateItem& PMItem);
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer ItemTags;


	
};
