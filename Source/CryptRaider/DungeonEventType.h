// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDungeonEventType : uint8
{
    Mover     UMETA(DisplayName = "Mover"),
    Rotator   UMETA(DisplayName = "Rotator")
    
};
