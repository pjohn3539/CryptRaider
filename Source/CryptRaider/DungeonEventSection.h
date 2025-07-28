// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventTriggerComponent.h"
#include "DungeonEventSection.generated.h"


// Declare the delegate signature
DECLARE_DELEGATE_OneParam(FOnSectionCompleted, FName);

/**
 * 
 */
USTRUCT(BlueprintType)
struct CRYPTRAIDER_API FDungeonEventSection
{
	GENERATED_BODY()

	FDungeonEventSection();

	void SetSectionActive(bool active);

	void SetSectionsUnlockedByCompletion(const TArray<FName>& activeList) { SectionsUnlockedByCompletion = activeList; }

	void Completed();

	// Delegate that external code (like the manager) can bind to
    FOnSectionCompleted OnCompleted;

	UPROPERTY(EditAnywhere)
    FName SectionName;

	UPROPERTY(EditAnywhere)
    bool SectionActive = false;

	UPROPERTY(EditAnywhere)
    TArray<FName> SectionsUnlockedByCompletion;
	
    TArray<UDungeonEventTriggerComponent*> ListOfDungeonEvents;

};
