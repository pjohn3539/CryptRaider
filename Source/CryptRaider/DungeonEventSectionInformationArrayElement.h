// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventSectionInformationArrayElement.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDungeonEventSectionInformationArrayElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool StartActive = false;

	UPROPERTY(EditAnywhere)
    TArray<FName> SectionsUnlockedByCompletion;

};
