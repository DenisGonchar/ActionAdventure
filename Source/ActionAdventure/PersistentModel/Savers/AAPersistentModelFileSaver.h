// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAPersistentModelSaver.h"
#include "UObject/Object.h"
#include "AAPersistentModelFileSaver.generated.h"


UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelFileSaver : public UAAPersistentModelSaver
{
	GENERATED_BODY()
public:
	virtual bool SaveStateToDefaultStorage(const struct FAAPMStateGame& StateGame) override;

	UFUNCTION(BlueprintCallable)
	bool SaveToSlot(const FAAPersistentModelSaveSlot& SaveSlot,  const FAAPMStateGame& StateGame);
  
private:

	bool SaveStateToFile(const FString& FileName, const FAAPMStateGame& StateGame);

};
