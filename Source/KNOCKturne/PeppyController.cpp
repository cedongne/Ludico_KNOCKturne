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

// GetCurrentLevel : Cast<ABattleFieldLevelScriptActor>(GetWorld()->GetLevelScriptActor());
}

void APeppyController::Interaction() {
	if (CanInteraction) {
		// TODO : 상호작용 가능할 때, Npc와의 대화를 시작하는 이벤트 호출. Npc와 대화 시작하면서 BP_Dialogue가 Viewport에 띄워지면 해당 플래그는 false로 변경 되어야 함.
	}
}