// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventComponent.h"
#include "DungeonEventComponentArray.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDungeonEventComponentArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
    TArray<UDungeonEventComponent*> Components;
};
