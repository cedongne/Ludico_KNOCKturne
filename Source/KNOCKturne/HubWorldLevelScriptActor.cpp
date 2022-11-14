// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	NTLOG(Warning, TEXT("Hubworld Level Script"));

	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueManager"));
	DialogueTableComponent->LoadDialogueTable("/Game/Assets/DataTable/Dialogue_Prologue.Dialogue_Prologue");
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	NTLOG_S(Warning);
}