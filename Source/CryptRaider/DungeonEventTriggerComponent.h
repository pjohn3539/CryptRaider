// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DungeonEvent.h"
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

	bool GetShouldReset() const { return shouldReset; }

	bool GetShouldNotTakeObject() const { return shouldNotTakeObject; }

private:

	UPROPERTY(EditAnywhere)
	FName tagNameForTrigger = "Key";

	UPROPERTY(EditAnywhere)
	FName AssociatedSectionName;
	
	UPROPERTY(EditAnywhere)
	float durationTimeForEvents = 4;

	UPROPERTY(EditAnywhere)
	bool onlyReactOnRelease = true;

	UPROPERTY(EditAnywhere)
	bool turnOffCollisonWhenActivated = false;
	
	UPROPERTY(EditAnywhere)
	bool shouldNotTakeObject = false;

	UPROPERTY(EditAnywhere, meta=(EditCondition="shouldNotTakeObject"))
	bool shouldReset = false;

	UPROPERTY(EditAnywhere)
	TArray<FDungeonEvent> dungeonEvents;

	AActor* CheckOverlappingActorsForTag() const;

};
