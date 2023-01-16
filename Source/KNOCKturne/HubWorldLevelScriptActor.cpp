// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"
#include "Engine/GameInstance.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueManager"));
	PrologueDialogueComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueMananger"));
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	DialogueTableComponent->LoadDialogueTable("Dialogue_Npc");
	PrologueDialogueComponent->LoadDialogueTable("Dialogue_Prologue");
}