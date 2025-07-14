// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEvent.h"

// Sets default values for this component's properties
UDungeonEvent::UDungeonEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void UDungeonEvent::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* mesh = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
	if (mesh) {
		originalCollisionEnabled = mesh->GetCollisionEnabled();
	}
}


// Called every frame
void UDungeonEvent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDungeonEvent::SetShouldActivate(bool active) {
	if (shouldReset) {
		ShouldActivate = active;
		if (turnOffCollisonWhenActivated) {
			SetCollisionEnabled(active);
		}
	} else if (!shouldReset && !HasActivated && active) {
		ShouldActivate = active;
		HasActivated = active;
		if (turnOffCollisonWhenActivated) {
			SetCollisionEnabled(active);
		}
	}
}

void UDungeonEvent::SetCollisionEnabled(bool active) {
	UStaticMeshComponent* mesh = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
	if (mesh) {
		if (active) {
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		} else {
			mesh->SetCollisionEnabled(originalCollisionEnabled);
		}
	}
}
