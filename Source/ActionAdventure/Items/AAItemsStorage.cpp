// Fill out your copyright notice in the Description page of Project Settings.


#include "AAItemsStorage.h"

#include "AAItem.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelFindHelpers.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelStatics.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSubsystem.h"


UAAItemsStorage* UAAItemSlot::GetItemStorage() const
{
	return GetTypedOuter<UAAItemsStorage>();
}

void UAAItemsStorage::InitItemsStorage()
{
	const int32 countSlotsToAdd = DefaultSlotsCount - Slots.Num(); 
	for (int32 i = 0; i < countSlotsToAdd; i++)
	{
		Slots.Add(NewObject<UAAItemSlot>(this));
	}
	
}

const TArray<UAAItemSlot*>& UAAItemsStorage::GetItemSlots() const
{
	return Slots;
}

bool UAAItemsStorage::AddItem(AAAItem* Item)
{	
	if (const auto itemSlot = FindSlotForItem(Item))
	{
		return AddItemToSlot(Item, itemSlot);
	}
	return false;
}

bool UAAItemsStorage::AddItemToSlot(AAAItem* Item, UAAItemSlot* ItemSlot)
{
	if (CanAddItemToSlot(Item, ItemSlot))
	{
		const auto oldItem = ItemSlot->Item;
		ItemSlot->Item = Item;

		const int32 itemSlotIndex = Slots.IndexOfByKey(ItemSlot);
		FAAPMStateItemsStorage* pmStorage = FindPMItemsStorage();
		Item->PersistentModelSpawn(pmStorage->Items[itemSlotIndex]);
		
		
		ItemSlot->OnItemSlotChangedDynamicDelegate.Broadcast(ItemSlot, oldItem);
		OnItemsStorageSlotChangedDynamicDelegate.Broadcast(this, ItemSlot, oldItem);

		return true;
	}
	return  false;
}

bool UAAItemsStorage::CanAddItemClass(TSubclassOf<AAAItem> ItemClass) const
{
	 return Slots.ContainsByPredicate([ItemClass, this](UAAItemSlot* Slot)
	{
		return CanAddItemClassToSlot(ItemClass, Slot);
	});
	
}

bool UAAItemsStorage::CanAddItemClassToSlot(TSubclassOf<AAAItem> ItemClass, UAAItemSlot* ItemSlot) const
{
	return ItemClass != nullptr && CanAddItemToSlot(ItemClass.GetDefaultObject(), ItemSlot); 
	
}

bool UAAItemsStorage::CanAddItemToSlot(AAAItem* Item, UAAItemSlot* ItemSlot) const
{
	return Item != nullptr && ItemSlot != nullptr && Slots.Contains(ItemSlot)
		&& ItemSlot->Item == nullptr && ItemSlot->ItemTagRequirements.RequirementsMet(Item->ItemTags);
}

bool UAAItemsStorage::RemoveItemFromSlot(UAAItemSlot* ItemSlot)
{
	if (CanRemoveItemFromSlot(ItemSlot))
	{
		const auto oldItem = ItemSlot->Item;
		
		ItemSlot->Item = nullptr;

		const int32 itemSlotIndex = Slots.IndexOfByKey(ItemSlot);
		FAAPMStateItemsStorage* pmStorage = FindPMItemsStorage();
		pmStorage->Items[itemSlotIndex] = FAAPMStateItem();
		
		ItemSlot->OnItemSlotChangedDynamicDelegate.Broadcast(ItemSlot, oldItem);
		OnItemsStorageSlotChangedDynamicDelegate.Broadcast(this, ItemSlot, oldItem);
		
		return true;
	}
	return false;
}

bool UAAItemsStorage::CanRemoveItemFromSlot(UAAItemSlot* ItemSlot) const
{
	return ItemSlot != nullptr && Slots.Contains(ItemSlot) && ItemSlot->Item != nullptr;
}

bool UAAItemsStorage::MoveItemToSlot(UAAItemSlot* SourceItemSlot, UAAItemsStorage* TargetItemStorage,
                                     UAAItemSlot* TargetItemSlot)
{
	if (CanMoveItemToSlot(SourceItemSlot, TargetItemStorage, TargetItemSlot))
	{
		TargetItemStorage->AddItemToSlot(SourceItemSlot->Item, TargetItemSlot);
		RemoveItemFromSlot(SourceItemSlot);
		return true;
		
	}
	return false;
	
}

bool UAAItemsStorage::CanMoveItemToSlot(UAAItemSlot* SourceItemSlot, UAAItemsStorage* TargetItemStorage,
                                        UAAItemSlot* TargetItemSlot) const
{
	return CanRemoveItemFromSlot(SourceItemSlot) && TargetItemStorage != nullptr
			&& TargetItemStorage->CanAddItemToSlot(SourceItemSlot->Item, TargetItemSlot);
	
}

UAAItemSlot* UAAItemsStorage::FindSlotForItem(AAAItem* Item)
{
	if (Item == nullptr)
	{
		return nullptr;
	}
	
	const auto itemSlotPtr = Algo::FindByPredicate(Slots,[Item, this](UAAItemSlot* ItemSlot)
	{
		return CanAddItemToSlot(Item, ItemSlot);
	});

	return itemSlotPtr != nullptr ? *itemSlotPtr : nullptr;
}

void UAAItemsStorage::PersistentModelSpawn(FAAPMStateItemsStorage& PMStorage)
{
	UAAPersistentModelConverter::PersistentModelSpawnObject(PMStorage, this);
	
	PMStorage.Items.AddDefaulted(Slots.Num());
}

void UAAItemsStorage::PersistentModelDeserialize(const FAAPMStateItemsStorage& PMStorage)
{
	//пока у нас нет механики изменения размера стораджа
	check(Slots.Num() == PMStorage.Items.Num());
	for (const auto slot : Slots)
	{
		RemoveItemFromSlot(slot);
	}

	for (int32 i = 0; i < PMStorage.Items.Num(); i++)
	{
		const auto& pmItem = PMStorage.Items[i];
		if (pmItem.Type.IsEmpty())
		{
			Slots[i]->Item = nullptr;
		}
		else
		{
			const auto newItem = CastChecked<AAAItem>(UAAPersistentModelConverter::SpawnObject(pmItem));
			AddItemToSlot(newItem, Slots[i]);
		}
		
	}

}

const FAAPersistentModelId& UAAItemsStorage::GetId() const
{
	return Id;
}

void UAAItemsStorage::SetId(const FAAPersistentModelId& NewId) 
{
	Id = NewId;
}

FAAPMStateItemsStorage* UAAItemsStorage::FindPMItemsStorage() const
{
	const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(this);
	if(persistentModelSubsystem == nullptr)
	{
		return nullptr;
	}

	const auto& pmGame = persistentModelSubsystem->GetState()->GetMutableStateGame();

	TArray<const FAAPMStateItemsStorage*> pmStorages = AAPMFindHelpers::FindValueProperties<FAAPMStateGame, FAAPMStateItemsStorage>(&pmGame);

	auto pmStoragePtr = Algo::FindByPredicate(pmStorages, [this](const
		FAAPMStateItemsStorage* PMStorage)
		{
			return PMStorage->Id == Id;
		});

	return pmStoragePtr != nullptr ? const_cast<FAAPMStateItemsStorage*>(*pmStoragePtr) : nullptr;
	
}
