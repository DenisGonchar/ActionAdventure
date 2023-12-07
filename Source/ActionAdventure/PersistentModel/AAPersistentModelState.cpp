// Fill out your copyright notice in the Description page of Project Settings.


#include "AAPersistentModelState.h"

void UAAPersistentModelState::SetStateGame(const FAAPMStateGame& InStateGame)
{
	StateGame = InStateGame;
}


const FAAPMStateGame& UAAPersistentModelState::GetStateGame() const 
{
	return StateGame;
}

FAAPMStateGame& UAAPersistentModelState::GetMutableStateGame()
{
	return bIsDeserializing ? DummyStateGame : StateGame;
}

void UAAPersistentModelState::SetPendingState(const FAAPMStateGame& InPendingStateGame)
{
	PendingState = InPendingStateGame;
}

const FAAPMStateGame& UAAPersistentModelState::GetPendingState()
{
	static FAAPMStateGame defaultValue;
	return PendingState.Get(defaultValue);
}

void UAAPersistentModelState::ResetPendingState()
{
	PendingState.Reset();
}

bool UAAPersistentModelState::HasPendingState() const
{
	return PendingState.IsSet();
}

void UAAPersistentModelState::OnStartDeserialize(const FAAPMStateGame& InStateGame)
{
	DummyStateGame = StateGame;
	bIsDeserializing = true;
	SetStateGame(InStateGame);
}

void UAAPersistentModelState::OnEndDeserialize()
{
	bIsDeserializing = false;
	DummyStateGame = {};
}

