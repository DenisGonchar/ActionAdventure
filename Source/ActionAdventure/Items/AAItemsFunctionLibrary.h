// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AAItemsFunctionLibrary.generated.h"

class AAAItem;

UCLASS()
class ACTIONADVENTURE_API UAAItemsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContext"))
	static AAAItem* CreateItem(const UObject* WorldContext, TSubclassOf<AAAItem> ItemClass);
	
};
