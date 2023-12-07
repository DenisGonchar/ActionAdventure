// Fill out your copyright notice in the Description page of Project Settings.


#include "AAItem.h"

#include "ActionAdventure/PersistentModel/AAPersistentModelStatics.h"


void AAAItem::UseFromInventory()
{
}

void AAAItem::PersistentModelSpawn(FAAPMStateItem& PMItem)
{
	UAAPersistentModelConverter::PersistentModelSpawnObject(PMItem, this);
}
