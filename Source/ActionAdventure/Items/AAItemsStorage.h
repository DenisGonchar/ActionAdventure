// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelIdInterface.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelTypes.h"
#include "UObject/Object.h"
#include "AAItemsStorage.generated.h"

class UAAItemsStorage;
class AAAItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemSlotChangedDynamicDelegate, UAAItemSlot*, ItemSlot, AAAItem*, OldItem);



UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class UAAItemSlot : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	UAAItemsStorage* GetItemStorage() const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AAAItem* Item;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagRequirements ItemTagRequirements;

	UPROPERTY(BlueprintAssignable)
	FOnItemSlotChangedDynamicDelegate OnItemSlotChangedDynamicDelegate;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemsStorageSlotChangedDynamicDelegate, UAAItemsStorage*, Storage, UAAItemSlot*, ItemSlot, AAAItem*, OldItem);


UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class ACTIONADVENTURE_API UAAItemsStorage : public UObject, public IAAPersistentModelIdInterface
{
	GENERATED_BODY()
public:

	void InitItemsStorage();

	UFUNCTION(BlueprintPure)
	const TArray<UAAItemSlot*>& GetItemSlots() const;
	
	UFUNCTION(BlueprintCallable)
	bool AddItem(AAAItem* Item);

	UFUNCTION(BlueprintCallable)
	bool AddItemToSlot(AAAItem* Item, UAAItemSlot* ItemSlot);

	UFUNCTION(BlueprintPure)
	bool CanAddItemClass(TSubclassOf<AAAItem> ItemClass) const;

	UFUNCTION(BlueprintPure)
	bool CanAddItemClassToSlot(TSubclassOf<AAAItem> ItemClass, UAAItemSlot* ItemSlot) const;

	UFUNCTION(BlueprintPure)
	bool CanAddItemToSlot(AAAItem* Item, UAAItemSlot* ItemSlot) const;
	
	UFUNCTION(BlueprintCallable)
	bool RemoveItemFromSlot(UAAItemSlot* ItemSlot);

	UFUNCTION(BlueprintPure)
	bool CanRemoveItemFromSlot(UAAItemSlot* ItemSlot) const;

	UFUNCTION(BlueprintCallable)
	bool MoveItemToSlot(UAAItemSlot* SourceItemSlot, UAAItemsStorage* TargetItemStorage, UAAItemSlot* TargetItemSlot);

	UFUNCTION(BlueprintPure)
	bool CanMoveItemToSlot(UAAItemSlot* SourceItemSlot, UAAItemsStorage* TargetItemStorage, UAAItemSlot* TargetItemSlot) const;
	
	UFUNCTION(BlueprintPure)
	UAAItemSlot* FindSlotForItem(AAAItem* Item);

	void PersistentModelSpawn(struct FAAPMStateItemsStorage& PMStorage);	
	void PersistentModelDeserialize(const struct FAAPMStateItemsStorage& PMStorage);
	
	virtual const FAAPersistentModelId& GetId() const override;
	virtual void SetId(const FAAPersistentModelId& NewId) override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnItemsStorageSlotChangedDynamicDelegate OnItemsStorageSlotChangedDynamicDelegate;

protected:
	FAAPMStateItemsStorage* FindPMItemsStorage() const;
	
protected:

	UPROPERTY(EditAnywhere)
	FAAPersistentModelId Id;
	
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UAAItemSlot*> Slots;

	UPROPERTY(EditDefaultsOnly)
	int32 DefaultSlotsCount;
	
};

