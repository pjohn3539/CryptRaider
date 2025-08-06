// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEventTriggerComponent.h"
#include "CryptRaiderGameplayTags.h"

// Sets default values for this component's properties
UDungeonEventTriggerComponent::UDungeonEventTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

// Called when the game starts
void UDungeonEventTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

    if (DungeonEventTriggerType == EDungeonEventTriggerType::ActionBased && !ComponentTags.Contains(CryptRaiderGameplayTags::ACTION_TRIGGER_TAG)) {
        ComponentTags.Add(CryptRaiderGameplayTags::ACTION_TRIGGER_TAG);
    }
    
    dungeonEvent.Setup();
}


void UDungeonEventTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (DungeonEventTriggerType == EDungeonEventTriggerType::PlacementBased) {
        
        AActor* actorFound = CheckOverlappingActorsForTag();

        if (actorFound) {
            UPrimitiveComponent*  component = Cast<UPrimitiveComponent>(actorFound->GetRootComponent());

            if (!placementBasedTriggerData.shouldNotTakeObject) {
                if (component) {
                    component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
                }
                actorFound->DisableComponentsSimulatePhysics();
            }

            if (!placementBasedTriggerData.shouldReset) {
                actorFound->Tags.Add(CryptRaiderGameplayTags::DEACTIVATED_TAG);
            }

            dungeonEvent.SetIsActive(true);
        } else {
            if (!placementBasedTriggerData.onlyReactOnRelease) {
                dungeonEvent.SetIsActive(false);
            }   
        }
    } else if (DungeonEventTriggerType == EDungeonEventTriggerType::MassBased) {
		float totalMass = 0.0f;

		TArray<AActor*> overlappingActors;
		GetOverlappingActors(overlappingActors);

        TArray<AActor*> overlappingNonGrabbedActors;

        if (overlappingActors.Num() > 0){
            for (AActor* actor : overlappingActors) {
                if (!actor->ActorHasTag(CryptRaiderGameplayTags::GRABBED_TAG)) {
                        overlappingNonGrabbedActors.Add(actor);
                }
            }
        }

		for (AActor* actor : overlappingNonGrabbedActors) {
			TArray<UPrimitiveComponent*> primitiveComponents;
			actor->GetComponents<UPrimitiveComponent>(primitiveComponents);

			for (UPrimitiveComponent* component : primitiveComponents) {
				if (component->IsSimulatingPhysics()) {
					totalMass += component->GetMass();
				}
			}
		}

		if (totalMass >= massBasedTriggerData.massNeeded) {
			dungeonEvent.SetIsActive(true);
		} else {
			dungeonEvent.SetIsActive(false);
		}
	}

    dungeonEvent.Tick(DeltaTime, durationTimeForEvents, AssociatedSectionName);
}

AActor* UDungeonEventTriggerComponent::CheckOverlappingActorsForTag() const {
    TArray<AActor*> overlappingActors;
    GetOverlappingActors(overlappingActors);

    if (overlappingActors.Num() > 0){
        for (AActor* actor : overlappingActors) {
           if ((actor->ActorHasTag(placementBasedTriggerData.tagNameForTrigger) && !actor->ActorHasTag(CryptRaiderGameplayTags::GRABBED_TAG)) 
           || (actor->ActorHasTag(placementBasedTriggerData.tagNameForTrigger) && !placementBasedTriggerData.onlyReactOnRelease && DungeonEventTriggerType == EDungeonEventTriggerType::PlacementBased)) {
                return actor;
           }
        }
    }

    return nullptr;
}

void UDungeonEventTriggerComponent::SetTriggerEnabled(bool active)
{
    SetGenerateOverlapEvents(active);
}