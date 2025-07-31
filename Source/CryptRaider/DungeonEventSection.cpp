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

void FDungeonEventSection::Completed()
{
    // bool completedAllSections = true;

    // for (UDungeonEventTriggerComponent* event : ListOfDungeonEvents) {
    //     // if (!event->GetCompletedStatus()) {

    //     // }
    // }

    // Notify whoever is listening (like the manager)
    // if (OnCompleted.IsBound())
    // {
    //     OnCompleted.Execute(SectionName);
    // }

    ///Activate other Sections
}

