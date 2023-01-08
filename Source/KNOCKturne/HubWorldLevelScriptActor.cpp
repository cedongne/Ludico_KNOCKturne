// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueManager"));
//	DialogueTableComponent->LoadDialogueTable("Dialogue_Prologue");
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	NTLOG_S(Warning);
}