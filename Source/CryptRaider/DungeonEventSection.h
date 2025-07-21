// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventComponentArray.h"
#include "DungeonEventSection.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CRYPTRAIDER_API FDungeonEventSection
{
	GENERATED_BODY()

	FDungeonEventSection();

	void Completed();

	UPROPERTY(EditAnywhere)
    FName SectionName;

	UPROPERTY(EditAnywhere)
    bool SectionActive;

	UPROPERTY(EditAnywhere)
    TArray<UDungeonEventComponent*> ListOfDungeonEvents;

};
