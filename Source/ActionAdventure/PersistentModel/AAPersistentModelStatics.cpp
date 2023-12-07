// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelStatics.h"

#include "AAPersistentModelIdInterface.h"
#include "AAPersistentModelSaveSlot.h"
#include "AAPersistentModelSettings.h"
#include "AAPersistentModelState.h"
#include "AAPersistentModelSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Loader/AAPersistentModelFileLoader.h"
#include "Misc/Paths.h"

FString UAAPersistentModelStatics::GetSaveDirectory()
{
	
	return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("PersistentModel"));
}

FString UAAPersistentModelStatics::GetSaveSlotPath(const FAAPersistentModelSaveSlot& SaveSlot)
{
	return FPaths::SetExtension(FPaths::Combine(GetSaveDirectory(), SaveSlot.SlotName), GetSaveSlotExtenstion());
}

TArray<FAAPersistentModelSaveSlot> UAAPersistentModelStatics::GetExistSaveSlots()
{
	auto& platfomFile = IPlatformFile::GetPlatformPhysical();

	TArray<FString> files;
	platfomFile.FindFiles(files, *GetSaveDirectory(), *GetSaveSlotExtenstion());

	TArray<FAAPersistentModelSaveSlot> slots;
	Algo::Transform(files, slots, [](const FString& FileName)
	{
		FAAPersistentModelSaveSlot slot;
		slot.SlotName = FPaths::GetBaseFilename(FileName);
		return slot;	
	});

	return slots; 
}

FAAPersistentModelSaveSlot UAAPersistentModelStatics::GetNewSaveSlot()
{
	int32 lastSlotIndex = 0;
	
	const auto saveSlots = GetExistSaveSlots();
	if (saveSlots.Num() > 0)
	{
		//SaveSlot12
		const auto& lastSlotName = saveSlots.Last().SlotName;
		const FString lastslotIndexString = lastSlotName.Right(lastSlotName.Len() - GetNewSaveSlotName().Len());

		lastSlotIndex = FCString::Atoi(*lastslotIndexString);
				
	}

	FAAPersistentModelSaveSlot newSlot;
	newSlot.SlotName = FString::Printf(TEXT("%s%d"), *GetNewSaveSlotName(), lastSlotIndex + 1);

	return newSlot;

}

FString UAAPersistentModelStatics::GetNewSaveSlotName()
{
	return TEXT("SaveSlot");
}

bool UAAPersistentModelStatics::LoadGameFromSlot(const UObject* Context, const FAAPersistentModelSaveSlot& SaveSlot)
{
	if (const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(Context))
	{
		FAAPMStateGame stateGame;
		if (persistentModelSubsystem->GetFileLoader()->LoadStateFromSlot(SaveSlot, stateGame))
		{
			LoadStateGame(Context, stateGame);
			persistentModelSubsystem->NotifyGameLoaded(SaveSlot);
			
			return true;
		}
	}

	return false;
}

void UAAPersistentModelStatics::LoadStateGame(const UObject* Context, const FAAPMStateGame& StateGame)
{
	
	if (const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(Context))
	{
		persistentModelSubsystem->GetState()->SetPendingState(StateGame);

		OpenDefaultGameMap(Context);

		
	}
}

void UAAPersistentModelStatics::OpenDefaultGameMap(const UObject* Context)
{
	
	if (const auto defaultMapWorld = UAAPersistentModelSettings::Get()->DefaultGameMap.LoadSynchronous())
	{
		const FString levelName = UWorld::RemovePIEPrefix(defaultMapWorld->GetMapName());
		UGameplayStatics::OpenLevel(Context, *levelName);
	}

}

FString UAAPersistentModelStatics::GetSaveSlotExtenstion()
{
	return TEXT(".Json");
}

void UAAPersistentModelConverter::PersistentModelSpawnObject(FAAPMStateObject& PMObject,
                                                             const TScriptInterface<IAAPersistentModelIdInterface>& Object)
{
	if (Object.GetObject() != nullptr)
	{
		PMObject.Type = FSoftObjectPath(Object.GetObject()->GetClass()).ToString();

		if (Object.GetObject()->Implements<UAAPersistentModelIdInterface>())
		{
			PMObject.Id = Object->GetId();
		}
	}
}

UObject* UAAPersistentModelConverter::SpawnObject(const FAAPMStateObject& PMObject, UObject* Outer /*= nullptr*/)
{
	if (PMObject.Type.IsEmpty())
	{
		UE_LOG(LogType, Warning, TEXT("UAAPersistentModelConverter::SpawnObject PMObject.Type is empty"));
		return nullptr;
	}

	const auto typePath = FSoftObjectPath(PMObject.Type);
	const auto ObjectType = typePath.TryLoad();

	if (const UClass* classType = Cast<UClass>(ObjectType))
	{
		const auto validOuter = Outer != nullptr ? Outer : GetTransientPackage();
		const auto spawnedObject = NewObject<UObject>(validOuter, classType);

		if (PMObject.Id.IsValid())
		{
			if (const auto idInterface = Cast<IAAPersistentModelIdInterface>(spawnedObject))
			{
				idInterface->SetId(PMObject.Id);
			}
		}

		return spawnedObject;
	}

	return nullptr;
	
}
