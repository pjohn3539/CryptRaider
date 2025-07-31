// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEvent.h"

void FDungeonEvent::Setup()
{
	if (DungeonEventType == EDungeonEventType::Mover)
	{
		moverData.Setup();
	}
	else if (DungeonEventType == EDungeonEventType::Rotator)
	{
		RotatorData.Setup();
	}
}

void FDungeonEvent::Tick(float DeltaTime, float duration, FName sectionName)
{
	if (DungeonEventType == EDungeonEventType::Mover)
	{
		moverData.Tick(DeltaTime, duration, IsActive, hasCompleted);
	}
	else if (DungeonEventType == EDungeonEventType::Rotator)
	{
		RotatorData.Tick(DeltaTime, duration, IsActive, hasCompleted);
	}

	if (hasCompleted && !hasCalledTheManager) {
		hasCalledTheManager = true;
		OnCompleted.Execute(sectionName);
	}
}
