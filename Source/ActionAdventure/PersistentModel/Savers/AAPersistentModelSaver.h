// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSaveSlot.h"
#include "UObject/Object.h"
#include "AAPersistentModelSaver.generated.h"


struct FAAPMStateGame;

UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelSaver : public UObject
{
	GENERATED_BODY()
public:
	virtual void Init();
	
	virtual bool SaveStateToDefaultStorage(const struct FAAPMStateGame& StateGame);

	void SetAutoSaveActivated(bool bActivated);

private:

	void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	
	void OnAutoSave();

	UFUNCTION()
	void OnGameLoaded(const FAAPersistentModelSaveSlot& SaveSlot);
protected:
	bool bActivatedAutoSave;
	FTimerHandle AutoSaveTimer;

	TOptional<FAAPersistentModelSaveSlot> LastSaveSlot;

	
};
