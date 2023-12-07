// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAPersistentModelTypes.h"
#include "Components/ActorComponent.h"
#include "AAPersistentModelEntityComponent.generated.h"

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class ACTIONADVENTURE_API UAAPersistentModelEntityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FAAPersistentModelId Id;
};
