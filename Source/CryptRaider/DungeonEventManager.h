// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonEventSection.h"
#include "DungeonEventManager.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API ADungeonEventManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonEventManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TArray<FName> SectionsActiveInTheBeginning;
	
	void SetupMap();
	
	void SetupActiveEventSections();

	UPROPERTY(EditAnywhere)
	TMap<FName, FDungeonEventSection> DungeonEventMap;
};
