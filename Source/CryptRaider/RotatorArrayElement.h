// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatorArrayElement.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRotatorArrayElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* rotatingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString nameOfMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator rotationOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMeshComponent* rotatingMeshComponent;

	FRotator originalRotation;

};
