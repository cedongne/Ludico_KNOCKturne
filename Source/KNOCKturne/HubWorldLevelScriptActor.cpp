// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	DialogueManager = CreateDefaultSubobject<UDialogueManager>(TEXT("DialogueManager"));
}
