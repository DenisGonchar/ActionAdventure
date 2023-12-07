
#pragma once

#include "CoreMinimal.h"
#include "AAItemEquipActor.generated.h"

UCLASS()
class ACTIONADVENTURE_API AAAItemEquipActor : public AActor
{
	GENERATED_BODY()
public:
	virtual void OnEquip();
	virtual void OnUnequip();

	
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnEquip"))
	void K2_OnEquip();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnUnequip"))
	void K2_OnUnequip();

	
};
