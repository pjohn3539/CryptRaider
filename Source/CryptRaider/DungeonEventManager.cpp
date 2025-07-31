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
            event->GetDungeonEvent().OnCompleted.BindUObject(this, &ADungeonEventManager::OnEventCompletion);
            section.ListOfDungeonEvents.Add(event);
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

void ADungeonEventManager::OnEventCompletion(FName sectionName)
{

    // Unlock additional sections or trigger other logic
    if (FDungeonEventSection* section = DungeonEventMap.Find(sectionName))
    {
        if (section->Completed()) {
            UE_LOG(LogTemp, Log, TEXT("Section '%s' completed."), *sectionName.ToString());

            for (const FName& unlockName : section->SectionsUnlockedByCompletion) {
                UE_LOG(LogTemp, Display, TEXT("Unlocking Section: %s"), *unlockName.ToString());
            
                if (FDungeonEventSection* unlockedSection = DungeonEventMap.Find(unlockName)) {
                    unlockedSection->SetSectionActive(true);
                } else {
                    UE_LOG(LogTemp, Error, TEXT("Section %s does not exist"), *unlockName.ToString());
                }
            
            }
        }
    } else {
        UE_LOG(LogTemp, Error, TEXT("Section %s does not exist"), *sectionName.ToString());
    }
}