// Fill out your copyright notice in the Description page of Project Settings.


#include "AAInventoryComponent.h"

#include "AAItemsFunctionLibrary.h"
#include "AAItemsStorage.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"

UAAInventoryComponent::UAAInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}

void UAAInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (const auto storage : Storages)
	{
		if (storage != nullptr)
		{
			storage->InitItemsStorage();
			storage->OnItemsStorageSlotChangedDynamicDelegate.AddDynamic(this, &UAAInventoryComponent::OnItemStorageChanged);
		}
	}

}

const TArray<UAAItemsStorage*> UAAInventoryComponent::GetStorages() const
{
	return Storages;
}

bool UAAInventoryComponent::AddItemByClass(TSubclassOf<AAAItem> ItemClass)
{
	const bool bCanAddItem = Storages.ContainsByPredicate([ItemClass](UAAItemsStorage* Storage)
	{
		return Storage->CanAddItemClass(ItemClass);
	});

	if (bCanAddItem)
	{
		const auto item = UAAItemsFunctionLibrary::CreateItem(this, ItemClass);
		return AddItem(item);
	}
	return  false;
}

bool UAAInventoryComponent::AddItem(AAAItem* Item)
{
	for (const auto& storage : Storages)
	{
		if (storage->AddItem(Item))
		{
			return true;
		}
	}
	return false;
	
}

void UAAInventoryComponent::PersistentModelSpawn(FAAPMStateInventory& PMInventory)
{
	for (const auto storage : Storages)
	{
		FAAPMStateItemsStorage& PmStorage = PMInventory.ItemsStorages.AddDefaulted_GetRef();
		storage->PersistentModelSpawn(PmStorage);
	}
	
}

void UAAInventoryComponent::PersistentModelDeserialize(const FAAPMStateInventory& PMInventory)
{
	check(Storages.Num() == PMInventory.ItemsStorages.Num());
	for (const auto storage : Storages)
	{
		if(const auto pmStoragePtr = Algo::FindBy(PMInventory.ItemsStorages, storage->GetId(), &FAAPMStateItemsStorage::Id))
		{
			storage->PersistentModelDeserialize(*pmStoragePtr);
		}
		
	}
}


void UAAInventoryComponent::OnItemStorageChanged(UAAItemsStorage* Storage, UAAItemSlot* ItemSlot, AAAItem* OldItem)
{
	OnInventorySlotChangedDynamicDelegate.Broadcast(this, ItemSlot, OldItem);
}

