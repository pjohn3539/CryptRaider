// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventType.h"
#include "MoverEventData.h"
#include "RotatorEventData.h"
#include "DungeonEvent.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CRYPTRAIDER_API  FDungeonEvent
{
	GENERATED_BODY()

public:

	bool GetIsMainEvent() const { return IsMainEvent; } 

	bool GetIsActive() const { return IsActive; } 

	void SetIsActive(bool active) { IsActive = active; } 

	void SetDurationTime(float newDurationTime)  { durationTime = newDurationTime; } 

	EDungeonEventType GetDungeonEventType() const { return DungeonEventType; }

	const FMoverEventData& GetMoverData() const { return moverData; }

	const FRotatorEventData& GetRotatorData() const { return RotatorData; }

	void Setup(AActor* Owner);

	void Tick(float DeltaTime);
private:

	UPROPERTY(EditAnywhere)
	bool IsMainEvent = true;

	UPROPERTY(EditAnywhere)
	bool IsActive = true;

	float durationTime = 4;

	UPROPERTY(EditAnywhere)
  	EDungeonEventType DungeonEventType = EDungeonEventType::Mover;

	UPROPERTY(
    EditAnywhere,
    Category="Mover",
    meta=(EditCondition="IsMainEvent && DungeonEventType == EDungeonEventType::Mover", EditConditionHides)
	)
	FMoverEventData moverData;

	UPROPERTY(
		EditAnywhere,
		Category="Rotator",
		meta=(EditCondition="IsMainEvent && DungeonEventType == EDungeonEventType::Rotator", EditConditionHides)
	)
	FRotatorEventData RotatorData;
	
};
