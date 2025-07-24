// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatorArrayElement.h"
#include "RotatorEventData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRotatorEventData  
{
	GENERATED_BODY()

	void Setup();

	void Tick(float DeltaTime, float Duration, bool IsActive);

	UPROPERTY(EditAnywhere)
	TArray<FRotatorArrayElement> listOfRotatingObjects; 
};
