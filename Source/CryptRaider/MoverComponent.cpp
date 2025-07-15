// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	originalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// //Get the address of the owner of this component.
	// AActor* Owner = GetOwner();

	// ///This de-references the pointer and allows you to see the value in Owner
	// //FString Name = (*Owner).GetActorNameOrLabel();

	// ///This does the same as the line above but shorter syntax
	// FString Name = Owner->GetActorNameOrLabel();
	// FVector Location = Owner->GetActorLocation();

	FVector targetLocation = originalLocation;

	if (ShouldActivate) {
		targetLocation = originalLocation + MoveOffset;
	} 

	FVector currentLocation = GetOwner()->GetActorLocation();
	float speed = MoveOffset.Length() / durationTime;

		// // %u specifier is used within the UE_LOG macro to format and display unsigned integer values in the output log. 
		// // It's a placeholder for an unsigned integer value, similar to how %d is used for signed integers
		// UE_LOG(LogTemp, Display, TEXT("Address of the Owner of the FC: %u"), Owner);

	FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);
	GetOwner()->SetActorLocation(newLocation);
}

