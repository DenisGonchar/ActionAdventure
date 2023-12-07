// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAAttributeSet.h"

#include "AADamageAttributeSet.generated.h"

UCLASS()
class ACTIONADVENTURE_API UAADamageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAADamageAttributeSet, Damage);

};
