// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AAInventoryComponent.generated.h"


class UAAItemsStorage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInventorySlotChangedDynamicDelegate, UAAInventoryComponent*, Inventory, UAAItemSlot*, ItemSlot, AAAItem*, OldItem);

UCLASS(meta=(BlueprintSpawnableComponent))
class ACTIONADVENTURE_API UAAInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAAInventoryComponent();
	
	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintPure)
	const TArray<UAAItemsStorage*> GetStorages() const;

	UFUNCTION(BlueprintCallable)
	bool AddItemByClass(TSubclassOf<AAAItem> ItemClass);

	UFUNCTION(BlueprintCallable)
	bool AddItem(AAAItem* Item);

	void PersistentModelSpawn(struct FAAPMStateInventory& PMInventory);
	void PersistentModelDeserialize(const struct FAAPMStateInventory& PMInventory);
	
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnInventorySlotChangedDynamicDelegate OnInventorySlotChangedDynamicDelegate;

protected:
	UFUNCTION()
	virtual void OnItemStorageChanged(UAAItemsStorage* Storage, UAAItemSlot* ItemSlot, AAAItem* OldItem);


protected:
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UAAItemsStorage*> Storages;

	
};
