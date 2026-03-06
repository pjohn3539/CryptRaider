// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventTriggerMassBasedData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDungeonEventTriggerMassBasedData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float massNeeded = 100;

	UPROPERTY(EditAnywhere)
	TArray<FName> ListOfTagNamesForTrigger;
	
};
