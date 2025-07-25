// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DungeonEventComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetDungeonEventComponents(TArray<UDungeonEventComponent*> newDungeonEventComponents);

private:

	UPROPERTY(EditAnywhere)
	FName tagNameForTrigger = "Key";

	UPROPERTY(EditAnywhere)
	TArray<UDungeonEventComponent*> dungeonEventComponents;

	UDungeonEventComponent* mainDungeonEventComponents;

	AActor* CheckOverlappingActorsForTag() const;
};
