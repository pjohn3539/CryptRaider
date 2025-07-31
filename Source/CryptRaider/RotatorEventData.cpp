// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RotatorEventData.h"

void FRotatorEventData::Setup()
{
	for (FRotatorArrayElement& element : listOfRotatingObjects)
	{
		if (!element.rotatingActor) continue;

		TArray<USceneComponent*> Components;
		element.rotatingActor->GetComponents<USceneComponent>(Components);

		for (USceneComponent* Comp : Components)
		{
			if (Comp->GetName() == element.nameOfMeshComponent)
			{
				element.rotatingMeshComponent = Comp;
				break;
			}
		}

		if (element.rotatingMeshComponent)
		{
			element.originalRotation = element.rotatingMeshComponent->GetComponentRotation();
		} else {
			element.rotatingMeshComponent = element.rotatingActor->GetRootComponent();
			element.originalRotation = element.rotatingMeshComponent->GetComponentRotation();
		}
	}
}

void FRotatorEventData::Tick(float DeltaTime, float Duration, bool IsActive, bool& HasCompleted)
{
	const float ArrivalTolerance = 0.1f;

	bool allCompleted = true;

	for (FRotatorArrayElement& element : listOfRotatingObjects)
	{
		if (!element.rotatingMeshComponent) continue;

		FRotator targetRotation = element.originalRotation;
		if (IsActive)
		{
			targetRotation += element.rotationOffset;
		}

		FRotator currentRotation = element.rotatingMeshComponent->GetComponentRotation();

		float speed = FVector(
			element.rotationOffset.Pitch,
			element.rotationOffset.Yaw,
			element.rotationOffset.Roll
		).Size() / Duration;

		FRotator newRotation = FMath::RInterpConstantTo(currentRotation, targetRotation, DeltaTime, speed);
		element.rotatingMeshComponent->SetWorldRotation(newRotation);

		 // Check if this element has arrived
        if (IsActive && !element.hasCompleted && currentRotation.Equals(targetRotation, ArrivalTolerance))
        {
            element.hasCompleted = true;
        }
        else if (!IsActive)
        {
            // Reset if going back
            element.hasCompleted = false;
        }

		if (!element.hasCompleted) {
			allCompleted = false;
		}
	}



	if (allCompleted) {
		HasCompleted = true;
	}
}