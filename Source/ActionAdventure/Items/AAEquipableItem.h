// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAItem.h"
#include "AAEquipableItem.generated.h"

struct FActiveGameplayEffectHandle;
class AAACharacter;
struct FGameplayModifierInfo;
class AAAItemEquipActor;
class UGameplayEffect;

UCLASS(Abstract)
class ACTIONADVENTURE_API AAAEquipableItem : public AAAItem
{
	GENERATED_BODY()

public:
	virtual void OnEquip();
	virtual void OnUnequip();

	UFUNCTION(BlueprintPure)
	AAACharacter* GetOwningCharacter() const;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> EquipEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayModifierInfo> EquipModifiers;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AAAItemEquipActor> EquipActorClass;

private:
	TArray<FActiveGameplayEffectHandle> EquippedEffectHandles;
};
