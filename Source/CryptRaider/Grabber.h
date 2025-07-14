// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void SetRotationMode(bool Active);

	UFUNCTION(BlueprintCallable)
	void RotateYaw(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void RotatePitch(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void AdjustHoldDistance(float AxisValue);
	
private:

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& outHitResult) const;

	bool IsAxisThresholdBelow(float axisValue) const;

	APlayerController* GetPlayerController() const;

	

	UPROPERTY(EditAnywhere)
	float maxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	float grabRadius = 100;

	
	bool rotationModeOn = false;
	FRotator CurrentRotationOffset = FRotator::ZeroRotator;
	FRotator RotationSpeed = FRotator(100.0f, 100.0f, 100.0f);
	UPROPERTY(EditAnywhere)
	float maxAxisThreshold = 0.1f;


	UPROPERTY(EditAnywhere)
	float holdDistance = 200;

	float originalHoldDistance;

	float CurrentHoldDistance = 0.0f;

	UPROPERTY(EditAnywhere)
	float minHoldDistance = 100.0f;

	UPROPERTY(EditAnywhere)
	float maxHoldDistance = 400.0f;

	UPROPERTY(EditAnywhere)
	float scrollSpeed = 50.0f;

	UPROPERTY(EditAnywhere)
	float holdDistanceInterpSpeed = 10.0f;

	const FName GRABBED_TAG = "Grabbed";


};
