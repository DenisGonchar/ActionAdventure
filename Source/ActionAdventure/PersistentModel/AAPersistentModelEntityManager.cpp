// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelEntityManager.h"

#include "AAPersistentModelState.h"
#include "ActionAdventure/Player/AAPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UAAPersistentModelEntityManager::AddEntityComponent(UAAPersistentModelEntityComponent* EntityComponent)
{
	EntityComponents.Add(EntityComponent);

}

void UAAPersistentModelEntityManager::RemoveEntityComponent(UAAPersistentModelEntityComponent* EntityComponent)
{
	EntityComponents.Remove(EntityComponent);
}

const TArray<UAAPersistentModelEntityComponent*>& UAAPersistentModelEntityManager::GetEntities() const
{
	return EntityComponents;
}

void UAAPersistentModelEntityManager::Deserialize(const FAAPMStateGame& PMGame)
{
	if (const auto playerCharacter = Cast<AAAPlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		playerCharacter->PersistentModelDeserialize(PMGame.Player);	
	}
	
}
