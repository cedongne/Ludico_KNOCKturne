// Fill out your copyright notice in the Description page of Project Settings.


#include "KNOCKturneLevelScriptActor.h"

AKNOCKturneLevelScriptActor::AKNOCKturneLevelScriptActor() {
	CommonDialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueTableManager"));
}