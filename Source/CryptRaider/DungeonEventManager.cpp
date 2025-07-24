// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonEventManager.h"


ADungeonEventManager::ADungeonEventManager() {
    //PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADungeonEventManager::BeginPlay()
{
	Super::BeginPlay();
    SetupMap();
    SetupActiveEventSections();
}

void ADungeonEventManager::SetupMap() {
    TArray<UDungeonEventComponent*> FoundEvents;

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
    {
        AActor* Actor = *ActorItr;
        if (!Actor)
        {
            continue;
        }

        // Get all components of type UDungeonEventComponent on this actor
        TArray<UDungeonEventComponent*> Events;
        Actor->GetComponents<UDungeonEventComponent>(Events);

        for (UDungeonEventComponent* event : Events) {
            UE_LOG(LogTemp, Display, TEXT("Event: %s"), *event->GetName());
            FName sectionName = event->GetAssociatedSectionName();
            FDungeonEventSection& section = DungeonEventMap.FindOrAdd(sectionName);

            if (section.SectionName.IsNone()) {
                section.SectionName = sectionName;
            }
            section.ListOfDungeonEvents.Add(event);
        }
    }
}

void ADungeonEventManager::SetupActiveEventSections(){

    
}