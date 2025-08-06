// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventTriggerActionBasedData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDungeonEventTriggerActionBasedData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float holdTimeToInteract = 2;
	
};
