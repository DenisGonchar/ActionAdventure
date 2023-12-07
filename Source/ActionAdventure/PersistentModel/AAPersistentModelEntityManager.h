// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AAPersistentModelEntityManager.generated.h"


class UAAPersistentModelEntityComponent;

UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelEntityManager : public UObject
{
	GENERATED_BODY()

public:
	void AddEntityComponent(UAAPersistentModelEntityComponent* EntityComponent);
	void RemoveEntityComponent(UAAPersistentModelEntityComponent* EntityComponent);

	const TArray<UAAPersistentModelEntityComponent*>& GetEntities() const;

	UFUNCTION(BlueprintCallable)
	void Deserialize(const struct FAAPMStateGame& PMGame);
	
private:
	UPROPERTY()
	TArray<UAAPersistentModelEntityComponent*> EntityComponents;
};
