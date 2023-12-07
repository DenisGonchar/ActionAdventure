// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AAPersistentModelSaveSlot.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "AAPersistentModelSubsystem.generated.h"

class UAAPersistentModelFileLoader;
class UAAPersistentModelFileSaver;
class UAAPersistentModelState;
class UAAPersistentModelEntityManager;

UCLASS()
class ACTIONADVENTURE_API UAAPersistentModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameLoadedDelegate, const FAAPersistentModelSaveSlot&, LoadedSlot);
	
public:
	UAAPersistentModelSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintPure)
	static UAAPersistentModelSubsystem* Get(const UObject* Context);

	UFUNCTION(BlueprintPure)
	UAAPersistentModelEntityManager* GetEntityManager() const;

	UFUNCTION(BlueprintPure)
	UAAPersistentModelState* GetState() const;

	UFUNCTION(BlueprintPure)
	UAAPersistentModelFileSaver* GetFileSaver() const;

	UFUNCTION(BlueprintPure)
	UAAPersistentModelFileLoader* GetFileLoader() const;

	void NotifyGameLoaded(const FAAPersistentModelSaveSlot& LoadedSlot);
	const TOptional<FAAPersistentModelSaveSlot>& GetLastLoadedSlot() const;
	
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameLoadedDelegate OnGameLoadedDelegate;
	
private:

	UPROPERTY()
	UAAPersistentModelEntityManager* EntityManager;

	UPROPERTY()
	UAAPersistentModelState* State;

	UPROPERTY()
	UAAPersistentModelFileSaver* FileSaver;
	
	UPROPERTY()
	UAAPersistentModelFileLoader* FileLoader;
	
	TOptional<FAAPersistentModelSaveSlot> LastLoadedSlot;
};
