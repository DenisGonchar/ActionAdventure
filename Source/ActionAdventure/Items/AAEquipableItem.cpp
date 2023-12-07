#include "AAEquipableItem.h"

#include "AbilitySystemComponent.h"
#include "ActionAdventure/Character/AACharacter.h"

void AAAEquipableItem::OnEquip()
{
	const auto owningCharacter = GetOwningCharacter();
	check(GetOwner() != nullptr);

	if (owningCharacter == nullptr)
	{
		return;
	}
	
	const auto abilitySystem = owningCharacter->GetAbilitySystemComponent();
	for (const auto effect : EquipEffects)
	{
		if (effect != nullptr)
		{
			const auto handler = abilitySystem->ApplyGameplayEffectToSelf(effect.GetDefaultObject(), 0.f, abilitySystem->MakeEffectContext());

			EquippedEffectHandles.Add(handler);
		}
	}

	UGameplayEffect* modifiersEffect = NewObject<UGameplayEffect>(this);
	modifiersEffect->DurationPolicy = EGameplayEffectDurationType::Infinite;
	for (const auto& modifier : EquipModifiers)
	{
		modifiersEffect->Modifiers.Add(modifier);
	}

	const auto handler = abilitySystem->ApplyGameplayEffectToSelf(modifiersEffect, 0.f, abilitySystem->MakeEffectContext());
	EquippedEffectHandles.Add(handler);

}

void AAAEquipableItem::OnUnequip()
{
	const auto owningCharacter = GetOwningCharacter();
	check(GetOwner() != nullptr);
	if (owningCharacter == nullptr)
	{
		return;
	}

	const auto abilitySystem = owningCharacter->GetAbilitySystemComponent();
	for (const auto& handle : EquippedEffectHandles)
	{
		abilitySystem->RemoveActiveGameplayEffect(handle);	
	}
	EquippedEffectHandles.Empty();
	
}

AAACharacter* AAAEquipableItem::GetOwningCharacter() const
{
	return GetOwner<AAACharacter>();
}
