// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MoverEventData.h"

void FMoverEventData::Setup(AActor* Owner)
{
	for (FMoverArrayElement& element : listOfMovingObjects)
	{
		if (!element.movingActor) continue;

		TArray<USceneComponent*> Components;
		element.movingActor->GetComponents<USceneComponent>(Components);

		for (USceneComponent* Comp : Components)
		{
			if (Comp->GetName() == element.nameOfMeshComponent)
			{
				element.movingMeshComponent = Comp;
				break;
			}
		}

		if (element.movingMeshComponent)
		{
			UE_LOG(LogTemp, Display, TEXT("Component Name: %s"), *element.movingMeshComponent->GetName());
			element.originalLocation = element.movingMeshComponent->GetComponentLocation();
		} else {
			UE_LOG(LogTemp, Display, TEXT("No component selected. Choosing Root Component"));
			element.movingMeshComponent = element.movingActor->GetRootComponent();
			element.originalLocation = element.movingMeshComponent->GetComponentLocation();
		}
	}
}


void FMoverEventData::Tick(float DeltaTime, float Duration, bool IsActive)
{
	for (FMoverArrayElement& element : listOfMovingObjects)
	{
		if (!element.movingMeshComponent) continue;

		FVector targetLocation = element.originalLocation;
		if (IsActive)
		{
			targetLocation += element.MoveOffset;
		}

		FVector currentLocation = element.movingMeshComponent->GetComponentLocation();

		float speed = element.MoveOffset.Length() / Duration;

		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);
		element.movingMeshComponent->SetWorldLocation(newLocation);
	}
}