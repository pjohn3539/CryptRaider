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
    SetupSectionMap();
    InitiateEventSections();
}

void ADungeonEventManager::SetupSectionMap() {

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
        TArray<UDungeonEventTriggerComponent*> Events;
        Actor->GetComponents<UDungeonEventTriggerComponent*>(Events);

        for (UDungeonEventTriggerComponent* event : Events) {
            
            FName sectionName = event->GetAssociatedSectionName();
            FDungeonEventSection& section = DungeonEventMap.FindOrAdd(sectionName);

            if (section.SectionName.IsNone()) {
                section.SectionName = sectionName;
            }
            section.ListOfDungeonEvents.Add(event);

            if (!section.OnCompleted.IsBound())
            {
                section.OnCompleted.BindUObject(this, &ADungeonEventManager::OnSectionCompleted);
            }
        }
    }
}

void ADungeonEventManager::InitiateEventSections() {

    TArray<FName> SectionKeys;
    SectionInformationMap.GetKeys(SectionKeys);

    for (const FName& key : SectionKeys) {
        FDungeonEventSectionInformationArrayElement* currentInformationSection = SectionInformationMap.Find(key);
        if (FDungeonEventSection* section = DungeonEventMap.Find(key))
        {
            section->SetSectionActive(currentInformationSection->StartActive);
            section->SetSectionsUnlockedByCompletion(currentInformationSection->SectionsUnlockedByCompletion);
        } else {
            UE_LOG(LogTemp, Display, TEXT("The following section could not be found in the variable DungeonEventMap: %s"), *key.ToString());
        }
    }
    
}

void ADungeonEventManager::OnSectionCompleted(FName CompletedSectionName)
{
    UE_LOG(LogTemp, Log, TEXT("Section '%s' completed."), *CompletedSectionName.ToString());

    // Unlock additional sections or trigger other logic
    if (FDungeonEventSection* Section = DungeonEventMap.Find(CompletedSectionName))
    {
        // for (const FName& UnlockName : Section->SectionsUnlockByCompletion)
        // {
        //     //UnlockSection(UnlockName);
        // }
    }
}