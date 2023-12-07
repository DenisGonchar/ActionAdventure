// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAGameMode.h"
#include "AAMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API AAAMainGameMode : public AAAGameMode
{
	GENERATED_BODY()
public:

	virtual void StartPlay() override;
	
};
