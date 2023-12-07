// Fill out your copyright notice in the Description page of Project Settings.


#include "AAGameplayStatics.h"

#include "ActionAdventure/Player/AAPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AAAPlayerCharacter* UAAGameplayStatics::GetPlayerCharacter(const UObject* WorldContext)
{
	return Cast<AAAPlayerCharacter>(UGameplayStatics::GetPlayerPawn(WorldContext, 0));
	
}
