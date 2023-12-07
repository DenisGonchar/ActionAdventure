// Fill out your copyright notice in the Description page of Project Settings.


#include "AAGameInstance.h"

#include "AbilitySystemGlobals.h"

void UAAGameInstance::Init()
{
	Super::Init();

	UAbilitySystemGlobals::Get().InitGlobalData();

}
