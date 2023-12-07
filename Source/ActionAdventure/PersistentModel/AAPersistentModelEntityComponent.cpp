// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelEntityComponent.h"

#include "AAPersistentModelEntityManager.h"
#include "AAPersistentModelSubsystem.h"

void UAAPersistentModelEntityComponent::OnRegister()
{
	Super::OnRegister();

	if (const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(this))
	{
		persistentModelSubsystem->GetEntityManager()->AddEntityComponent(this);
	}
}

void UAAPersistentModelEntityComponent::OnUnregister()
{
	Super::OnUnregister();

	if (const auto persistentModelSubsystem = UAAPersistentModelSubsystem::Get(this))
	{
		persistentModelSubsystem->GetEntityManager()->RemoveEntityComponent(this);
	}
}
