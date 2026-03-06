// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventTriggerPlacementBasedData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDungeonEventTriggerPlacementBasedData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FName> ListOfTagNamesForTrigger;

	UPROPERTY(EditAnywhere)
	bool onlyReactOnRelease = true;

	UPROPERTY(EditAnywhere)
	bool turnOffCollisonWhenActivated = false;
	
	UPROPERTY(EditAnywhere)
	bool shouldNotTakeObject = false;

	UPROPERTY(EditAnywhere, meta=(EditCondition="shouldNotTakeObject"))
	bool shouldReset = false;
	
};
