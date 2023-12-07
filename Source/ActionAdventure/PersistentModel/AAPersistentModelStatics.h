// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAPersistentModelIdInterface.h"
#include "AAPersistentModelState.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AAPersistentModelStatics.generated.h"

struct FAAPersistentModelSaveSlot;
/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FString GetSaveDirectory();

	static FString GetSaveSlotPath(const FAAPersistentModelSaveSlot& SaveSlot);

	static FString GetSaveSlotExtenstion();

	UFUNCTION(BlueprintCallable)	
	static TArray<FAAPersistentModelSaveSlot> GetExistSaveSlots();

	UFUNCTION(BlueprintPure)	
	static FAAPersistentModelSaveSlot GetNewSaveSlot();

	/*Return only SaveSlot name without index*/
	static FString GetNewSaveSlotName();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = Context))	
	static bool LoadGameFromSlot(const UObject* Context, const FAAPersistentModelSaveSlot& SaveSlot);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = Context))	
	static void LoadStateGame(const UObject* Context, const FAAPMStateGame& StateGame);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = Context))	
	static void OpenDefaultGameMap(const UObject* Context);
	
};

UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelConverter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void PersistentModelSpawnObject(struct FAAPMStateObject& PMObject, const TScriptInterface<IAAPersistentModelIdInterface>& Object);

	static UObject* SpawnObject(const struct FAAPMStateObject& PMObject, UObject* Outer = nullptr);
};
