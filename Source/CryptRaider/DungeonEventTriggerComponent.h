// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DungeonEvent.h"
#include "DungeonEventTriggerType.h"
#include "DungeonEventTriggerActionBasedData.h"
#include "DungeonEventTriggerMassBasedData.h"
#include "DungeonEventTriggerPlacementBasedData.h"
#include "DungeonEventTriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDungeonEventTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDungeonEventTriggerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	FName GetAssociatedSectionName() const { return AssociatedSectionName; }
	
	bool GetShouldReset() const { return placementBasedTriggerData.shouldReset; }

	bool GetShouldNotTakeObject() const { return placementBasedTriggerData.shouldNotTakeObject; }

	FDungeonEvent& GetDungeonEvent() { return dungeonEvent; }

	void SetTriggerEnabled(bool active);

	UFUNCTION(BlueprintCallable)
	EDungeonEventTriggerType GetDungeonEventTriggerType() { return DungeonEventTriggerType; }

	UFUNCTION(BlueprintCallable)
	void SetDungeonEventIsActive(bool active) { dungeonEvent.SetIsActive(active); }

private:

	UPROPERTY(EditAnywhere)
	FName AssociatedSectionName;
	
	UPROPERTY(EditAnywhere)
	float durationTimeForEvents = 4;

	UPROPERTY(EditAnywhere)
  	EDungeonEventTriggerType DungeonEventTriggerType = EDungeonEventTriggerType::PlacementBased;

	UPROPERTY(
    EditAnywhere,
    meta=(EditCondition="DungeonEventTriggerType == EDungeonEventTriggerType::PlacementBased", EditConditionHides)
	)
	FDungeonEventTriggerPlacementBasedData placementBasedTriggerData;

	UPROPERTY(
    EditAnywhere,
    meta=(EditCondition="DungeonEventTriggerType == EDungeonEventTriggerType::MassBased", EditConditionHides)
	)
	FDungeonEventTriggerMassBasedData massBasedTriggerData;

	UPROPERTY(
    EditAnywhere,
    meta=(EditCondition="DungeonEventTriggerType == EDungeonEventTriggerType::ActionBased", EditConditionHides)
	)
	FDungeonEventTriggerActionBasedData actionBasedTriggerData;

	UPROPERTY(EditAnywhere)
	FDungeonEvent dungeonEvent;

	AActor* CheckOverlappingActorsForTag() const;

};
