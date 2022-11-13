// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	NTLOG(Warning, TEXT("Hubworld Level Script"));
	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueManager"));
	DialogueTableComponent->LoadDialogueTable("/Game/Assets/DataTable/Dialogue_Prologue.Dialogue_Prologue");

	auto DataRow = DialogueTableComponent->GetData("Prologue_2");
	NTLOG(Warning, TEXT("%s"), *(DataRow->CharacterStringID));
//	DialogueManager = CreateDefaultSubobject<UDialogueManager>(TEXT("DialogueManager"));
}
