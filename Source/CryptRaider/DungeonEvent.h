// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventType.h"
#include "MoverEventData.h"
#include "RotatorEventData.h"
#include "DungeonEvent.generated.h"


// Declare the delegate signature
DECLARE_DELEGATE_OneParam(FOnEventCompletion, FName);

/**
 * 
 */
USTRUCT(BlueprintType)
struct CRYPTRAIDER_API  FDungeonEvent
{
	GENERATED_BODY()

public:

	bool GetIsActive() const { return IsActive; } 

	bool GetHasCompleted() const { return hasCompleted; }

	void SetIsActive(bool active) { IsActive = active; } 

	EDungeonEventType GetDungeonEventType() const { return DungeonEventType; }

	const FMoverEventData& GetMoverData() const { return moverData; }

	const FRotatorEventData& GetRotatorData() const { return RotatorData; }

	void Setup();

	void Tick(float DeltaTime, float duration, FName sectionName);

	// Delegate that external code (like the manager) can bind to
    FOnEventCompletion OnCompleted;

private:

	UPROPERTY(EditAnywhere)
	bool IsActive = false;

	bool hasCalledTheManager = false;

	UPROPERTY(EditAnywhere)
	bool hasCompleted = false;

	UPROPERTY(EditAnywhere)
  	EDungeonEventType DungeonEventType = EDungeonEventType::Mover;

	UPROPERTY(
    EditAnywhere,
    Category="Mover",
    meta=(EditCondition="DungeonEventType == EDungeonEventType::Mover", EditConditionHides)
	)
	FMoverEventData moverData;

	UPROPERTY(
		EditAnywhere,
		Category="Rotator",
		meta=(EditCondition="DungeonEventType == EDungeonEventType::Rotator", EditConditionHides)
	)
	FRotatorEventData RotatorData;
	
};
