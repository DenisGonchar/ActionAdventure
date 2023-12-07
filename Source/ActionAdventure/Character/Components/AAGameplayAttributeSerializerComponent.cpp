// Fill out your copyright notice in the Description page of Project Settings.


#include "AAGameplayAttributeSerializerComponent.h"

#include "AbilitySystemGlobals.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelEntityComponent.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelFindHelpers.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelSubsystem.h"


void UAAGameplayAttributeSerializerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const auto abilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		for ( const auto& attribute : AttributesToSerialize)
		{
			abilitySystem->GetGameplayAttributeValueChangeDelegate(attribute).AddUObject(this,
				&UAAGameplayAttributeSerializerComponent::OnAttributeChanged);
		}
	}
}

void UAAGameplayAttributeSerializerComponent::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(this);
	if(persistentModelSubsystem == nullptr)
	{
		return;
	}

	UAAPersistentModelEntityComponent* EntityComponent = GetOwner()->FindComponentByClass<UAAPersistentModelEntityComponent>();
	if (EntityComponent == nullptr)
	{
		return;
	}
	
	const auto& pmGame = persistentModelSubsystem->GetState()->GetMutableStateGame();

	TArray<const FAAPMStateActor*> pmActors = AAPMFindHelpers::FindValueProperties<FAAPMStateGame,
		FAAPMStateActor>(&pmGame);
	
	const auto pmActorPtr = Algo::FindByPredicate(pmActors, [EntityComponent](const
		FAAPMStateActor* PMActor)
		{
			return PMActor->Id == EntityComponent->Id;
		});

	if (pmActorPtr == nullptr)
	{
		return;
	}

	auto& pmActor = const_cast<FAAPMStateActor&>(**pmActorPtr);

	FAAPMAttribute* pmAttributePtr = Algo::FindByPredicate(pmActor.Attributes, [Data](const FAAPMAttribute& PMAttribute)
		{
			return PMAttribute.Attribute == Data.Attribute;
		});

	if (pmAttributePtr == nullptr)
	{
		pmAttributePtr = &pmActor.Attributes.AddDefaulted_GetRef();
		pmAttributePtr->Attribute = Data.Attribute;
		
	}

	pmAttributePtr->Value = Data.NewValue;
}
