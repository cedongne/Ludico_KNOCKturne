// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"
#include "Engine/GameInstance.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	PrologueDialogueComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueMananger"));
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
	PeppyController = (APeppyController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	DialogueTableComponent->LoadDialogueTable("Dialogue_Npc");
	PrologueDialogueComponent->LoadDialogueTable("Dialogue_Prologue");
}

//void AHubWorldLevelScriptActor::StartPrologueDialogue() {
//	PeppyController->PrologueInProcess = true;
//	PrologueDialogueComponent->ResetDialogueRowPointer();
//
//	 // BP_Dialogue 위젯 생성
//	if (DialogueWidgetClass) {
//		DialogueWidgetRef = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
//		if (DialogueWidgetRef) {
//			DialogueWidgetRef->AddToViewport();
//		}
//	}
//
//	DialogueWidgetRef->TextBlock_E->SetVisibility(ESlateVisibility::Visible);
//	
//	 //Get Actor of Class(BP_DreamM)
//	 //Set Actor Rotation (0.0, 0.0, -70.0)
//
//	DialogueWidgetRef->GetNextDialogueLine(PrologueDialogueComponent);
//}
//
//bool AHubWorldLevelScriptActor::MoveDirectionTF(FDialogueData DataTable) {
//	if (DataTable.Direction.Contains("DT")) {
//		return true;
//	}
//	else if (DataTable.Direction.Contains("DF")) {
//		return false;
//	}
//	else {
//		return NULL;
//	}
//}
//
//void AHubWorldLevelScriptActor::StorePrevCameraRotation() {
//	PrevCameraRotation = Peppy->Camera->GetComponentRotation();
//}
//
//void AHubWorldLevelScriptActor::StorePrevCameraLocation() {
//	PrevCameraLocation = Peppy->Camera->GetComponentLocation();
//}
//
//void AHubWorldLevelScriptActor::StorePrevCameraTransform() {
//	StorePrevCameraLocation();
//	StorePrevCameraRotation();
//}
//
//void AHubWorldLevelScriptActor::PrologueDirection(FDialogueData DataTable) {
//	if (DataTable.Direction.Contains("none")) {
//		CallMoveDirection(DataTable);
//	}
//	else if (DataTable.Direction.Contains("before")) {
//		BlackScreenOff();
//		CallMoveDirection(DataTable);
//	}
//	else if (DataTable.Direction.Contains("after")) {
//		CallMoveDirection(DataTable);
//		BlackScreenOn();
//	}
//	else if (DataTable.Direction.Contains("both")) {
//		BlackScreenOff();
//		CallMoveDirection(DataTable);
//		BlackScreenOn();
//	}
//}
//
//void AHubWorldLevelScriptActor::CallMoveDirection(FDialogueData DataTable) {
//	bool isDirectionExist = MoveDirectionTF(DataTable);
//
//	if (isDirectionExist) {
//		MoveDirection();
//		MDSelection++;
//	}
//	else {
//		DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
//		DialogueWidgetRef->SetVisibility(ESlateVisibility::Visible);
//	}
//}
//
//void AHubWorldLevelScriptActor::NextIsDirection(FDialogueData DataTable) {
//	if (DataTable.Direction == "-1") {
//		DialogueWidgetRef->isDirection = false;
//	}
//	else {
//		DialogueWidgetRef->isDirection = true;
//	}
//}
//
//void AHubWorldLevelScriptActor::AfterPrologueDirection() {
//	DialogueWidgetRef->isCameraMoving = false;
//	DialogueWidgetRef->RichTextBlock_Dialogue->SetText(FText::FromString(""));
//	DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
//	DialogueWidgetRef->SetVisibility(ESlateVisibility::Visible);
//}
//
//void AHubWorldLevelScriptActor::SetPeppyHiddenOrNot() {
//	if (isPrologue) {
//		if (KNOCKturneGameState->isBattleFail) {
//			Peppy->SetActorHiddenInGame(true);
//		}
//		else {
//			Peppy->SetActorHiddenInGame(false);
//		}
//	}
//	else {
//		Peppy->SetActorHiddenInGame(true);
//	}
//}
//
//void AHubWorldLevelScriptActor::BattleFailDialogueAllEnded() {
//	DialogueWidgetRef->RemoveFromParent();
//
//	if (KNOCKturneGameState->isDreamDiaryUpdated) {
//		KNOCKturneGameState->isDreamDiaryUpdated = false;
//	}
//	if (KNOCKturneGameState->GetDreamFragment) {
//		KNOCKturneGameState->GetDreamFragment = false;
//	}
//	Peppy->Camera->SetWorldTransform(OriginalCameraTransform);
//	Peppy->SetActorHiddenInGame(false);
//}
//
//void AHubWorldLevelScriptActor::CreateHubworldHUD() {
//	if (HubworldHUDClass) {
//		HubworldHUDRef = CreateWidget<UHubworldHUDWidget>(GetWorld(), HubworldHUDClass);
//		if (HubworldHUDRef) {
//			HubworldHUDRef->AddToViewport();
//		}
//	}
//
//	if (KNOCKturneGameState->isDreamDiaryUpdated) {
//		HubworldHUDRef->Image_DreamDiary_Updated->SetVisibility(ESlateVisibility::Visible);
//	}
//	else {
//		HubworldHUDRef->Image_DreamDiary_Updated->SetVisibility(ESlateVisibility::Hidden);
//	}
//}