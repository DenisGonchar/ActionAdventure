// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelFileLoader.h"

#include "JsonObjectConverter.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelStatics.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSaveSlot.h"

bool UAAPersistentModelFileLoader::LoadStateToDefaultStorage(FAAPMStateGame& OutStateGame)
{
	return Super::LoadStateToDefaultStorage(OutStateGame);
	
}

bool UAAPersistentModelFileLoader::LoadStateFromSlot(const FAAPersistentModelSaveSlot& SaveSlot,
	FAAPMStateGame& OutStateGame)
{
	return LoadStateFromFile(UAAPersistentModelStatics::GetSaveSlotPath(SaveSlot),OutStateGame);

}

bool UAAPersistentModelFileLoader::LoadStateFromFile(const FString& FileName, FAAPMStateGame& OutStateGame)
{
	FString stateGameString;

	if(!FFileHelper::LoadFileToString(stateGameString, *FileName))
	{
		return false;
	}

	return FJsonObjectConverter::JsonObjectStringToUStruct(stateGameString, &OutStateGame);

}
