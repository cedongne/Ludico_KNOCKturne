// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
	IsHoverMouse = false;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
//	SetInteractionPopupWidget(InteractionPopupWidget);
}


void ANPC::SetCanInteraction_Implementation() {

}

void ANPC::SetCannotInteraction_Implementation() {

}