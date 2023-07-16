// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyController.h"

#include "BattleFieldLevelScriptActor.h"

APeppyController::APeppyController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

// Called to bind functionality to input
void APeppyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interaction / Use Special Skill", EInputEvent::IE_Pressed, this, &APeppyController::Interaction);
}

void APeppyController::BeginPlay() {
	Super::BeginPlay();

	CurrentLevelScriptActor = Cast<AKNOCKturneLevelScriptActor>(GetWorld()->GetLevelScriptActor());
}
void APeppyController::Interaction() {
	BP_Interaction();
}