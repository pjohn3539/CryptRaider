// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEventSection.h"

FDungeonEventSection::FDungeonEventSection()
{
}

void FDungeonEventSection::Completed()
{
    bool completedAllSections = true;

    for (UDungeonEventComponent* event : ListOfDungeonEvents) {
        if (!event->GetCompletedStatus()) {

        }
    }

    ///Activate other Sections
}


void FDungeonEventSection::SetSectionActive(bool active)
{
    SectionActive = active;

}