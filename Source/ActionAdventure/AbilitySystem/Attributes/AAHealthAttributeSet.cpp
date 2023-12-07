// Fill out your copyright notice in the Description page of Project Settings.


#include "AAHealthAttributeSet.h"

void UAAHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == UAAHealthAttributeSet::GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UAAHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == UAAHealthAttributeSet::GetMaxHealthAttribute() && NewValue > GetHealth())
	{
		SetHealth(NewValue);
	}
}
