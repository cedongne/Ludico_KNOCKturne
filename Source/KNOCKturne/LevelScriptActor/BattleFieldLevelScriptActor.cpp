// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleFieldLevelScriptActor.h"

ABattleFieldLevelScriptActor::ABattleFieldLevelScriptActor(){
}

void ABattleFieldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	CommonDialogueTableComponent->LoadDialogueTable("Dialogue_EP1_Battle");
}
