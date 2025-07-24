// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonEventComponent.generated.h"


UCLASS( ClassGroup=(Custom))
class CRYPTRAIDER_API UDungeonEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDungeonEventComponent();

	void SetCollisionEnabled(bool active);

	bool GetShouldReset() const { return shouldReset; }

	bool GetShouldTakeObject() const { return shouldTakeObject; }

	bool GetOnlyReactOnRelease() const { return onlyReactOnRelease; }

	bool GetTurnOffCollisonWhenActivated() const { return turnOffCollisonWhenActivated; } 

	FName GetAssociatedSectionName() const { return AssociatedSectionName; }

	bool GetCompletedStatus() const { return completed; } 

	bool GetIsMainEvent() const { return IsMainEvent; } 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldActivate(bool active);

	void MakeObjectNoLongerInteractable();

protected:

	UPROPERTY(EditAnywhere)
	bool IsMainEvent = true;

	UPROPERTY(EditAnywhere)
	FName AssociatedSectionName;

	ECollisionEnabled::Type originalCollisionEnabled;
	
	UPROPERTY(EditAnywhere)
	float durationTime = 4;

	UPROPERTY(EditAnywhere)
	bool ShouldActivate = false;

	UPROPERTY(EditAnywhere)
	bool turnOffCollisonWhenActivated = false;
	
	UPROPERTY(EditAnywhere)
	bool shouldReset = false;

	UPROPERTY(EditAnywhere)
	bool shouldTakeObject = true;

	UPROPERTY(EditAnywhere)
	bool onlyReactOnRelease = true;

	bool HasActivated = false;

	bool completed = false;

};
