// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoverArrayElement.h"
#include "MoverEventData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMoverEventData 
{
	GENERATED_BODY()

	void Setup(AActor* Owner);

	void Tick(float DeltaTime, float Duration, bool IsActive);

	UPROPERTY(EditAnywhere)
	TArray<FMoverArrayElement> listOfMovingObjects; 
};
