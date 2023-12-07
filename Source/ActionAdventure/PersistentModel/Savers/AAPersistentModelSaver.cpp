// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelSaver.h"

#include "ActionAdventure/PersistentModel/AAPersistentModelSettings.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSubsystem.h"

void UAAPersistentModelSaver::Init()
{
	if (const  auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(this))
	{
		persistentModelSubsystem->OnGameLoadedDelegate.AddDynamic(this, &UAAPersistentModelSaver::OnGameLoaded);
	}
}

bool UAAPersistentModelSaver::SaveStateToDefaultStorage(const FAAPMStateGame& StateGame)
{
	unimplemented();

	return true;
	
}

void UAAPersistentModelSaver::SetAutoSaveActivated(bool bActivated)
{
	if (!UAAPersistentModelSettings::Get()->bAutoSaveEnabled)
	{
		return;
	}
	if (bActivatedAutoSave == bActivated)
	{
		return;
	}

	bActivatedAutoSave = bActivated;
	
	if (bActivated)
	{
		FWorldDelegates::OnWorldCleanup.AddUObject(this, &UAAPersistentModelSaver::OnWorldCleanup);

		if (const auto world = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::ReturnNull))
		{
			world->GetTimerManager().SetTimer(AutoSaveTimer, this, &UAAPersistentModelSaver::OnAutoSave,
				UAAPersistentModelSettings::Get()->AutoSaveTime, true);
		}
	}
	else
	{
		FWorldDelegates::OnWorldCleanup.RemoveAll(this);

		if (const auto world = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::ReturnNull))
		{
			world->GetTimerManager().ClearTimer(AutoSaveTimer);
		}
	}
}

void UAAPersistentModelSaver::OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	SetAutoSaveActivated(false);
	
}

void UAAPersistentModelSaver::OnAutoSave()
{
	SaveStateToDefaultStorage(UAAPersistentModelSubsystem::Get(this)->GetState()->GetStateGame());
}

void UAAPersistentModelSaver::OnGameLoaded(const FAAPersistentModelSaveSlot& SaveSlot)
{
	LastSaveSlot = SaveSlot;
}
