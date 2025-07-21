// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventComponent.h"
#include "RotatorArrayElement.h"
#include "RotatorEventComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API URotatorEventComponent : public UDungeonEventComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatorEventComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Setup();

private: 

	UPROPERTY(EditAnywhere)
	TArray<FRotatorArrayElement> listOfRotatingObjects; 

};
