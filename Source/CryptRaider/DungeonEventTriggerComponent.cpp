// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEventTriggerComponent.h"
#include "Components/MeshComponent.h"
#include "CryptRaiderGameplayTags.h"
#include "CryptRaiderCharacter.h"

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

    // if (DungeonEventTriggerType == EDungeonEventTriggerType::PlacementBased ) {
    //     ListOfTagNamesForTrigger = placementBasedTriggerData.;ListOfTagNamesForTrigger
    // } else if (DungeonEventTriggerType == EDungeonEventTriggerType::MassBased) {
    //     ListOfTagNamesForTrigger = 
    // }
    
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

            if (!placementBasedTriggerData.shouldReset && !actorFound->ActorHasTag(CryptRaiderGameplayTags::DEACTIVATED_TAG)) {
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

        //UE_LOG(LogTemp, Display, TEXT("Length of Overlapping Actors: %s"), *FString::FromInt(overlappingActors.Num()));

        if (overlappingActors.Num() > 0){
            for (AActor* actor : overlappingActors) {
                if (!actor->ActorHasTag(CryptRaiderGameplayTags::GRABBED_TAG)) {
                        overlappingNonGrabbedActors.Add(actor);
                }
            }
        }

        //UE_LOG(LogTemp, Display, TEXT("Length of Overlapping Non Grabbed Actors: %s"), *FString::FromInt(overlappingNonGrabbedActors.Num()));

		for (AActor* actor : overlappingNonGrabbedActors) {

            if (!actor->ActorHasTag(CryptRaiderGameplayTags::PLAYER)) {
                TArray<UPrimitiveComponent*> primitiveComponents;
                actor->GetComponents<UPrimitiveComponent>(primitiveComponents);

                for (UPrimitiveComponent* component : primitiveComponents) {
                    if (component->IsSimulatingPhysics()) {
                        totalMass += component->GetMass();
                    }
                }
            } else {
                ACryptRaiderCharacter* player =  Cast<ACryptRaiderCharacter>(actor);

                totalMass += player->GetMass();

                // UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(actor->GetRootComponent());

                // if (primitive)
                // {
                //     totalMass += primitive->GetMass();
                // }

            }
		}

        UE_LOG(LogTemp, Display, TEXT("Total Mass: %s"), *FString::FromInt(totalMass));

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

        bool HasMatchingTag = false;

        // for (const FName& Tag : ListOfTagNamesForTrigger)
        // {
        //     if (actor->ActorHasTag(Tag))
        //     {
        //         HasMatchingTag = true;
        //         break;
        //     }
        // }

        for (AActor* actor : overlappingActors) {
           if ((HasMatchingTag && !actor->ActorHasTag(CryptRaiderGameplayTags::GRABBED_TAG)) 
           || (HasMatchingTag && !placementBasedTriggerData.onlyReactOnRelease && DungeonEventTriggerType == EDungeonEventTriggerType::PlacementBased)) {
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

void UDungeonEventTriggerComponent::ApplyOverlay(UMaterialInterface* grabOverlayMaterial) {
	if (!grabOverlayMaterial) {
		return;
	}

    for (UMeshComponent* mesh : highlightedMeshes)
	{
        if (!mesh) {
            return;
        }
        
        mesh->SetOverlayMaterial(grabOverlayMaterial);
    }
}

void UDungeonEventTriggerComponent::ClearOverlay() {

    for (UMeshComponent* mesh : highlightedMeshes)
    {
        mesh->SetOverlayMaterial(nullptr);
        mesh = nullptr;
    }
}