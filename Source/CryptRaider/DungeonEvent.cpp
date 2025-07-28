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

void FDungeonEvent::Tick(float DeltaTime)
{
	if (DungeonEventType == EDungeonEventType::Mover)
	{
		moverData.Tick(DeltaTime, durationTime, IsActive);
	}
	else if (DungeonEventType == EDungeonEventType::Rotator)
	{
		RotatorData.Tick(DeltaTime, durationTime, IsActive);
	}
}
