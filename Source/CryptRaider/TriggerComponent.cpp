// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "CryptRaiderGameplayTags.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* actorFound = CheckOverlappingActorsForTag();

    if (actorFound) {
        UPrimitiveComponent*  component = Cast<UPrimitiveComponent>(actorFound->GetRootComponent());

        if (dungeonEventComponent->GetShouldTakeObject()) {
            if (component) {
                component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
            }
            actorFound->DisableComponentsSimulatePhysics();
        }

        if (!dungeonEventComponent->GetShouldReset()) {
		    actorFound->Tags.Add(CryptRaiderGameplayTags::DEACTIVATED_TAG);
        }

        dungeonEventComponent->SetShouldActivate(true);
    } else {
        dungeonEventComponent->SetShouldActivate(false);
    }
}

void UTriggerComponent::SetDungeonEventComponent(UDungeonEventComponent* newDungeonEventComponent) {
    dungeonEventComponent = newDungeonEventComponent;
}

AActor* UTriggerComponent::CheckOverlappingActorsForTag() const {
    TArray<AActor*> overlappingActors;
    GetOverlappingActors(overlappingActors);

    if (overlappingActors.Num() > 0){
        for (AActor* actor : overlappingActors) {
           if ((actor->ActorHasTag(tagNameForTrigger) && !actor->ActorHasTag(CryptRaiderGameplayTags::GRABBED_TAG)) 
           || (actor->ActorHasTag(tagNameForTrigger) && !dungeonEventComponent->GetOnlyReactOnRelease())) {
                return actor;
           }
        }
    }

    return nullptr;
}