// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAPersistentModelTypes.h"
#include "AttributeSet.h"
#include "UObject/Object.h"
#include "AAPersistentModelState.generated.h"

USTRUCT(BlueprintType)
struct FAAPMStateObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FAAPersistentModelId Id;

	UPROPERTY(BlueprintReadOnly)
	FString Type;
	
};

USTRUCT(BlueprintType)
struct FAAPMAttribute
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(BlueprintReadOnly)
	float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FAAPMStateActor : public FAAPMStateObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FTransform Transform;

	UPROPERTY(BlueprintReadOnly)
	TArray<FAAPMAttribute> Attributes;
	
};

USTRUCT(BlueprintType)
struct FAAPMStateItem : public FAAPMStateObject
{
	GENERATED_BODY()
public:
		

	
};
USTRUCT(BlueprintType)
struct FAAPMStateItemsStorage : public FAAPMStateObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FAAPMStateItem> Items;


	
};

USTRUCT(BlueprintType)
struct FAAPMStateInventory : public FAAPMStateObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FAAPMStateItemsStorage> ItemsStorages;

	
};


USTRUCT(BlueprintType)
struct FAAPMStatePlayer : public FAAPMStateActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FAAPMStateInventory Inventory;

	UPROPERTY(BlueprintReadOnly)
	FAAPMStateInventory Equipment;
	
};

USTRUCT(BlueprintType)
struct FAAPMStateGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FAAPMStatePlayer Player;

	
};


UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelState : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	void SetStateGame(const FAAPMStateGame& InStateGame);

	UFUNCTION(BlueprintPure)
	const FAAPMStateGame& GetStateGame() const;

	UFUNCTION(BlueprintPure)
	FAAPMStateGame& GetMutableStateGame();

	void SetPendingState(const FAAPMStateGame& InPendingStateGame);
	const FAAPMStateGame& GetPendingState();

	void ResetPendingState();
	bool HasPendingState() const;

	void OnStartDeserialize(const FAAPMStateGame& InStateGame);
	void OnEndDeserialize();
	
private:
	UPROPERTY()
	FAAPMStateGame StateGame;

	FAAPMStateGame DummyStateGame;

	TOptional<FAAPMStateGame> PendingState;

	bool bIsDeserializing = false;
};
