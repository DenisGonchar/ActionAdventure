// Fill out your copyright notice in the Description page of Project Settings.


#include "AAItemsFunctionLibrary.h"
#include "AAItem.h"


AAAItem* UAAItemsFunctionLibrary::CreateItem(const UObject* WorldContext, TSubclassOf<AAAItem> ItemClass)
{
	const auto world = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull);
	
	if(world == nullptr || ItemClass == nullptr)
	{
		return nullptr;
		
	}

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	return world->SpawnActor<AAAItem>(ItemClass, spawnParameters);	
		
}
