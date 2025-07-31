// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonEventSection.h"
#include "DungeonEventSectionInformationArrayElement.h"
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

	void UnlockSection(FName sectionName);

	// UFUNCTION()
	// void OnSectionCompleted(FName CompletedSectionName);

	UFUNCTION()
	void OnEventCompletion(FName sectionName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	void SetupSectionMap();
	
	void InitiateEventSections();

	UPROPERTY(EditAnywhere)
	TMap<FName, FDungeonEventSection> DungeonEventMap;

	UPROPERTY(EditAnywhere)
	TMap<FName, FDungeonEventSectionInformationArrayElement> SectionInformationMap;
};
