// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MoverEventData.h"

void FMoverEventData::Setup(AActor* Owner)
{
    dataOwner = Owner;
	originalLocation = dataOwner->GetActorLocation();
}


void FMoverEventData::Tick(float DeltaTime, float Duration, bool IsActive)
{
    FVector targetLocation = originalLocation;

	if (IsActive)
	{
		targetLocation = originalLocation + MoveOffset;
	} 

    UE_LOG(LogTemp, Display, TEXT("Target Vector: %s"), *targetLocation.ToString());
	FVector currentLocation = dataOwner->GetActorLocation();
	float speed = MoveOffset.Length() / Duration;

	FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);
	dataOwner->SetActorLocation(newLocation);
}