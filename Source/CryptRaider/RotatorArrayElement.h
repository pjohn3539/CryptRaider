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

	UPROPERTY(EditAnywhere)
	UMeshComponent* rotatingMeshComponent;

	UPROPERTY(EditAnywhere)
	FRotator RotationOffset;

	FRotator originalRotation;

};
