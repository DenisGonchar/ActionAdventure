// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAPersistentModelLoader.h"
#include "UObject/Object.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSaveSlot.h"
#include "AAPersistentModelFileLoader.generated.h"

UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelFileLoader : public UAAPersistentModelLoader
{
	GENERATED_BODY()
public:
	virtual bool LoadStateToDefaultStorage(FAAPMStateGame& OutStateGame) override;

	UFUNCTION(BlueprintCallable)
	bool LoadStateFromSlot(const FAAPersistentModelSaveSlot& SaveSlot, FAAPMStateGame& OutStateGame);
	
private:
	bool LoadStateFromFile(const FString& FileName, FAAPMStateGame& OutStateGame);
};
