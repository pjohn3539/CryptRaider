// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoverArrayElement.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMoverArrayElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* movingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString nameOfMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MoveOffset;
	
	USceneComponent* movingMeshComponent;

	FVector originalLocation;

};
