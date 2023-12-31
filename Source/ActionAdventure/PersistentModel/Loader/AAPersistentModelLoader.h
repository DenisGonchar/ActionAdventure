// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AAPersistentModelLoader.generated.h"


UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelLoader : public UObject
{
	GENERATED_BODY()

public:
	virtual bool LoadStateToDefaultStorage(struct FAAPMStateGame& OutStateGame);
};
