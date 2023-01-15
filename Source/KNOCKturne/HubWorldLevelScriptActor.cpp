// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"
#include "Engine/GameInstance.h"
#include "KNOCKturneGameInstance.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueManager"));

//	GameInstance = GetGameInstance<UKNOCKturneGameInstance>();
//	DialogueSubsystem = GameInstance->GetSubsystem<UDialogueSubsystem>();
//	DialogueSubsystem->Test();

}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	DialogueTableComponent->LoadDialogueTable("Dialogue_Prologue");
	NTLOG_S(Warning);
}