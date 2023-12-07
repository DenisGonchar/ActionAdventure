// Fill out your copyright notice in the Description page of Project Settings.


#include "AAMainGameMode.h"

#include "ActionAdventure/PersistentModel/AAPersistentModelEntityManager.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSubsystem.h"
#include "ActionAdventure/PersistentModel/Savers/AAPersistentModelFileSaver.h"

void AAAMainGameMode::StartPlay()
{
	Super::StartPlay();

	const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(this);
	
	const auto persistentModelState = persistentModelSubsystem->GetState();
	if (persistentModelState->HasPendingState())
	{
		persistentModelState->OnStartDeserialize(persistentModelState->GetPendingState());
		persistentModelState->ResetPendingState();
		
		persistentModelSubsystem->GetEntityManager()->Deserialize(persistentModelState->GetStateGame());

		persistentModelState->OnEndDeserialize();
	}

	persistentModelSubsystem->GetFileSaver()->SetAutoSaveActivated(true);
}
 