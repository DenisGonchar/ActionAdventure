// Fill out your copyright notice in the Description page of Project Settings.


#include "AAAbilitySystem.h"

void UAAAbilitySystem::InitializeComponent()
{
	Super::InitializeComponent();

	for (const auto attribute : DefaultAttributes)
	{
		if (attribute != nullptr)
		{
			GetOrCreateAttributeSubobject(attribute);
		}
	}
	
	for (const auto effect : DefaultEffects)
	{
		if (effect != nullptr)
		{
			ApplyGameplayEffectToSelf(effect.GetDefaultObject(), 0.f, MakeEffectContext());
		}
	}
	
}
