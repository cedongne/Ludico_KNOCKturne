// Fill out your copyright notice in the Description page of Project Settings.


#include "PrologueLevelScriptActor.h"

APrologueLevelScriptActor::APrologueLevelScriptActor() {
	DialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueTableComponent"));
	DialogueTableComponent->LoadDialogueTable("Dialogue_Prologue");
}