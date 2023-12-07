// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelSubsystem.h"

#include "AAPersistentModelEntityManager.h"
#include "AAPersistentModelState.h"
#include "Loader/AAPersistentModelFileLoader.h"
#include "Savers/AAPersistentModelFileSaver.h"

UAAPersistentModelSubsystem::UAAPersistentModelSubsystem()
{
	EntityManager = CreateDefaultSubobject<UAAPersistentModelEntityManager>("EntityManager");

	State = CreateDefaultSubobject<UAAPersistentModelState>("State");

	FileSaver = CreateDefaultSubobject<UAAPersistentModelFileSaver>("FileSaver");

	FileLoader = CreateDefaultSubobject<UAAPersistentModelFileLoader>("FileLoader");
	
}

void UAAPersistentModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FileSaver->Init();
}

UAAPersistentModelSubsystem* UAAPersistentModelSubsystem::Get(const UObject* Context)
{
	const auto world = GEngine->GetWorldFromContextObject(Context, EGetWorldErrorMode::LogAndReturnNull);
	if (world == nullptr)
	{
		return nullptr;
	}

	
	const auto gameInstance = world->GetGameInstance();
	
	return gameInstance != nullptr ? gameInstance->GetSubsystem<UAAPersistentModelSubsystem>() : nullptr;
	
}

UAAPersistentModelEntityManager* UAAPersistentModelSubsystem::GetEntityManager() const
{
	return EntityManager;
}

UAAPersistentModelState* UAAPersistentModelSubsystem::GetState() const
{
	return State;
}

UAAPersistentModelFileSaver* UAAPersistentModelSubsystem::GetFileSaver() const
{
	return FileSaver;
}

UAAPersistentModelFileLoader* UAAPersistentModelSubsystem::GetFileLoader() const
{
	return FileLoader;
}

void UAAPersistentModelSubsystem::NotifyGameLoaded(const FAAPersistentModelSaveSlot& LoadedSlot)
{
	LastLoadedSlot = LoadedSlot;
	OnGameLoadedDelegate.Broadcast(LastLoadedSlot.GetValue());
}

const TOptional<FAAPersistentModelSaveSlot>& UAAPersistentModelSubsystem::GetLastLoadedSlot() const
{
	return LastLoadedSlot;
}
