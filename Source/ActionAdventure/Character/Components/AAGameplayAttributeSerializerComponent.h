// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "AAGameplayAttributeSerializerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONADVENTURE_API UAAGameplayAttributeSerializerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<FGameplayAttribute> AttributesToSerialize;
	
private:
	void OnAttributeChanged(const struct FOnAttributeChangeData& Data);

};

