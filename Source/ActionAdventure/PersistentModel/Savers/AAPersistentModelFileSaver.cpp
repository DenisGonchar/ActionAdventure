// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelFileSaver.h"

#include "JsonObjectConverter.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSaveSlot.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelStatics.h"

bool UAAPersistentModelFileSaver::SaveStateToDefaultStorage(const FAAPMStateGame& StateGame)
{
	return SaveToSlot(LastSaveSlot.Get(UAAPersistentModelStatics::GetNewSaveSlot()), StateGame);
	
}

bool UAAPersistentModelFileSaver::SaveToSlot(const FAAPersistentModelSaveSlot& SaveSlot, const FAAPMStateGame& StateGame)
{
	LastSaveSlot = SaveSlot;
	return SaveStateToFile(UAAPersistentModelStatics::GetSaveSlotPath(SaveSlot), StateGame);
	
}

bool UAAPersistentModelFileSaver::SaveStateToFile(const FString& FileName, const FAAPMStateGame& StateGame)
{
	FString stateGameString;
	FJsonObjectConverter::UStructToJsonObjectString(StateGame, stateGameString);

	return FFileHelper::SaveStringToFile(stateGameString, *FileName);
	
}
