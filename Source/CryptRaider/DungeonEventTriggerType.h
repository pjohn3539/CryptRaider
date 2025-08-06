// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventTriggerType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDungeonEventTriggerType : uint8
{
    PlacementBased     UMETA(DisplayName = "Placement Based"),
    MassBased   UMETA(DisplayName = "Mass Based"),
    ActionBased   UMETA(DisplayName = "Action Based")
};
