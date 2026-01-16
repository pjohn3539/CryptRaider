// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEventSection.h"

FDungeonEventSection::FDungeonEventSection()
{
}

void FDungeonEventSection::SetSectionActive(bool active) {
    SectionActive = active;

    for (UDungeonEventTriggerComponent* event : ListOfDungeonEvents) {
        if (!event) continue;
        
        event->SetTriggerEnabled(active);
    }
}

bool FDungeonEventSection::Completed()
{
    bool completedAllEvents = true;

    for (UDungeonEventTriggerComponent* event : ListOfDungeonEvents) {
        bool bIsActive = false;
        FString BoolAsString = event->GetDungeonEvent().GetHasCompleted() ? TEXT("true") : TEXT("false");

        
        UE_LOG(LogTemp, Warning, TEXT("Bool as String: %s"), *BoolAsString);
        if (!event->GetDungeonEvent().GetHasCompleted()) {
            completedAllEvents = false;
            break;
        }
    }

    return completedAllEvents;
}

