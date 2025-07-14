// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	originalHoldDistance = holdDistance;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	CurrentHoldDistance = FMath::FInterpTo(CurrentHoldDistance, holdDistance, DeltaTime, holdDistanceInterpSpeed);

	//A perk in C++ is that it will check the conditional left to right for a conditional and 
	//if the condition on the left is false it won't check the right. This allows you to do the below.
	//Though you are dereferenceing PhysicsHandle on the right which could be an issue if it was null, but
	//due to the left condition being false it won't make it to the right condition allowing this to be a valid
	//condition statement.
	if (physicsHandle && physicsHandle->GetGrabbedComponent()) {
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * CurrentHoldDistance;
		FRotator targetRotation = GetComponentRotation() + CurrentRotationOffset;

		physicsHandle->SetTargetLocationAndRotation(targetLocation, targetRotation);
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& outHitResult)  const {
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * maxGrabDistance;

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(grabRadius);
	bool HasHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	return HasHit;
}

void UGrabber::Grab() {

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr) {
		return;
	}

	FHitResult HitResult;

	if (GetGrabbableInReach(HitResult)) {
		CurrentHoldDistance = holdDistance;
		
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add(GRABBED_TAG);
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		physicsHandle->GrabComponentAtLocationWithRotation(
				HitComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation()
		);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		//UE_LOG(LogTemp, Display, TEXT("The actor that has been hit: %s"), *HitResult.GetActor()->GetActorNameOrLabel());
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No Actor hit"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const {

	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle != nullptr) {
		return physicsHandle;
	}

	UE_LOG(LogTemp, Warning, TEXT("UPhysicsHandleComponent is missing on Player"));
	return nullptr;

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Display, TEXT("Released"));

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	//A perk in C++ is that it will check the conditional left to right for a conditional and 
	//if the condition on the left is false it won't check the right. This allows you to do the below.
	//Though you are dereferenceing PhysicsHandle on the right which could be an issue if it was null, but
	//due to the left condition being false it won't make it to the right condition allowing this to be a valid
	//condition statement.
	if (physicsHandle && physicsHandle->GetGrabbedComponent()) {
			AActor* GrabbedActor = physicsHandle->GetGrabbedComponent()->GetOwner();
			GrabbedActor->Tags.Remove(GRABBED_TAG);
			physicsHandle->ReleaseComponent();
			CurrentRotationOffset = FRotator::ZeroRotator;
			holdDistance = originalHoldDistance;
	} 
	
}

void UGrabber::SetRotationMode(bool Active) {

	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	APlayerController* playerController = GetPlayerController();

	if (physicsHandle == nullptr || playerController == nullptr) {
		return;
	}

	if (physicsHandle->GetGrabbedComponent() != nullptr) {
		rotationModeOn = Active;
		playerController->SetIgnoreLookInput(Active);
	} else {
		UE_LOG(LogTemp, Display, TEXT("Currently the player is not holding an object."));
		rotationModeOn = false;
		playerController->SetIgnoreLookInput(false);
	}


}

void UGrabber::RotateYaw(float AxisValue){
	if (!rotationModeOn || IsAxisThresholdBelow(AxisValue)) {
		return;
	}
	
	CurrentRotationOffset.Yaw += AxisValue * RotationSpeed.Yaw * GetWorld()->GetDeltaSeconds();
}

void UGrabber::RotatePitch(float AxisValue){
	if (!rotationModeOn || IsAxisThresholdBelow(AxisValue)) {
		return;
	}
	
	CurrentRotationOffset.Pitch += AxisValue * RotationSpeed.Pitch * GetWorld()->GetDeltaSeconds();

	UE_LOG(LogTemp, Display, TEXT("CurrentRotationOffset Value: %s"), *CurrentRotationOffset.ToCompactString());
}

bool UGrabber::IsAxisThresholdBelow(float axisValue) const{
	return FMath::Abs(axisValue) <= maxAxisThreshold;
}

APlayerController* UGrabber::GetPlayerController() const {
		APawn* ownerPawn = Cast<APawn>(GetOwner());
		if (ownerPawn)
		{
			APlayerController* playerController = Cast<APlayerController>(ownerPawn->GetController());
			if (playerController)
			{
				return playerController;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Failed to get Player Controller"));
		return nullptr;
}

void UGrabber::AdjustHoldDistance(float AxisValue)
{
	if (FMath::IsNearlyZero(AxisValue, 0.01f)) {
		return;
	}

	holdDistance += AxisValue * scrollSpeed;
	holdDistance = FMath::Clamp(holdDistance, minHoldDistance, maxHoldDistance);

	UE_LOG(LogTemp, Display, TEXT("Hold Distance Adjusted: %f"), holdDistance);
}

