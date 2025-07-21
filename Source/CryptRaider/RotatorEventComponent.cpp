// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorEventComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
URotatorEventComponent::URotatorEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotatorEventComponent::BeginPlay()
{
	Super::BeginPlay();

	Setup();
	//SetDungeonEvent
	
}

// Called every frame
void URotatorEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	for (FRotatorArrayElement element : listOfRotatingObjects)
	{
		FRotator targetRotation = element.originalRotation;

		if (ShouldActivate) {
			targetRotation = element.originalRotation + element.rotationOffset;
		} 

		FRotator currentRotation = element.rotatingMeshComponent->GetComponentRotation();
		float speed = FVector(
			element.rotationOffset.Pitch,
			element.rotationOffset.Yaw,
			element.rotationOffset.Roll
		).Size() / durationTime;


		FRotator newRotation = FMath::RInterpConstantTo(currentRotation, targetRotation, DeltaTime, speed);
		element.rotatingMeshComponent->SetWorldRotation(newRotation);
	}

}

void URotatorEventComponent::Setup() {
	for (FRotatorArrayElement& element : listOfRotatingObjects) {

		TArray<UStaticMeshComponent*> Components;
		UStaticMeshComponent* meshComponent = nullptr;

		if (!element.rotatingActor)
		{
			UE_LOG(LogTemp, Fatal, TEXT("RotatorComponent::Setup - Null actor in rotating object list!"));
			continue; // or return; or break; depending on behavior you want
		}

    	element.rotatingActor->GetComponents<UStaticMeshComponent>(Components);

		for (UStaticMeshComponent* Component : Components)
		{
			if (Component && Component->GetName() == element.nameOfMeshComponent)
			{
				element.rotatingMeshComponent = Component;
				break;
			}
		}

		if (!element.rotatingMeshComponent){
			UE_LOG(LogTemp, Fatal, TEXT("Invalid Component Name: %s"), *element.nameOfMeshComponent);
		}

		element.originalRotation = element.rotatingMeshComponent->GetComponentRotation();

	}

}