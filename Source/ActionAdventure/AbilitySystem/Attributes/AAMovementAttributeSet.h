// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAAttributeSet.h"

#include "AAMovementAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONADVENTURE_API UAAMovementAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UAAMovementAttributeSet, MovementSpeed);

};
