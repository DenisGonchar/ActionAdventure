#include "AAEquipmentComponent.h"

#include "AAEquipableItem.h"
#include "AAItemsStorage.h"


void UAAEquipmentComponent::OnItemStorageChanged(UAAItemsStorage* Storage, UAAItemSlot* ItemSlot, AAAItem* OldItem)
{
	Super::OnItemStorageChanged(Storage, ItemSlot, OldItem);

	if (const auto equipableItem = Cast<AAAEquipableItem>(OldItem))
	{
		equipableItem->OnUnequip();
		equipableItem->SetOwner(nullptr);
	}

	if (const auto equipableItem = Cast<AAAEquipableItem>(ItemSlot->Item))
	{
		equipableItem->SetOwner(GetOwner());
		equipableItem->OnEquip();
	}
	
}
