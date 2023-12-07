// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAInventoryComponent.h"
#include "Components/ActorComponent.h"
#include "AAEquipmentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONADVENTURE_API UAAEquipmentComponent : public UAAInventoryComponent
{
	GENERATED_BODY()

public:


protected:
	virtual void OnItemStorageChanged(UAAItemsStorage* Storage, UAAItemSlot* ItemSlot, AAAItem* OldItem) override;
	
};
