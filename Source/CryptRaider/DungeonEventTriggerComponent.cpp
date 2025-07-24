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

    for (FDungeonEvent& event : dungeonEvents)
	{
		event.Setup(GetOwner());
	}
}


void UDungeonEventTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

      AActor* actorFound = CheckOverlappingActorsForTag();

    if (actorFound) {
        UPrimitiveComponent*  component = Cast<UPrimitiveComponent>(actorFound->GetRootComponent());

        if (!shouldNotTakeObject) {
            if (component) {
                component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
            }
            actorFound->DisableComponentsSimulatePhysics();
        }

        if (!shouldReset) {
		    actorFound->Tags.Add(CryptRaiderGameplayTags::DEACTIVATED_TAG);
        }

        for (FDungeonEvent& event: dungeonEvents) {
            event.SetIsActive(true);
        }
    } else {
        for (FDungeonEvent& event: dungeonEvents) {
            event.SetIsActive(false);
        }
    }

    for (FDungeonEvent& event : dungeonEvents)
    {
        event.Tick(DeltaTime);
    }
}

AActor* UDungeonEventTriggerComponent::CheckOverlappingActorsForTag() const {
    TArray<AActor*> overlappingActors;
    GetOverlappingActors(overlappingActors);

    if (overlappingActors.Num() > 0){
        for (AActor* actor : overlappingActors) {
           if ((actor->ActorHasTag(tagNameForTrigger) && !actor->ActorHasTag(CryptRaiderGameplayTags::GRABBED_TAG)) 
           || (actor->ActorHasTag(tagNameForTrigger) && !onlyReactOnRelease)) {
                return actor;
           }
        }
    }

    return nullptr;
}