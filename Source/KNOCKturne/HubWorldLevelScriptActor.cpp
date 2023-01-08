// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueManager"));
<<<<<<< Updated upstream
	DialogueTableComponent->LoadDialogueTable("Dialogue_Prologue");
=======
//	DialogueTableComponent->LoadDialogueTable("Dialogue_Prologue");
>>>>>>> Stashed changes
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	NTLOG_S(Warning);
}