// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamM.h"
#include "LevelScriptActor/HubWorldLevelScriptActor.h"

ADreamM::ADreamM()
{
	
}

void ADreamM::BeginPlay()
{
	Super::BeginPlay();
	
	Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ADreamM::SelectDialogue() {
	if (DialogueWidgetRef->Image_Dialogue_Select_1->GetVisibility() == ESlateVisibility::Visible) {
		DialogueWidgetRef->Image_Dialogue_Select_1->SetVisibility(ESlateVisibility::Hidden);
		DialogueWidgetRef->Image_Dialogue_Select_2->SetVisibility(ESlateVisibility::Hidden);
		DialogueWidgetRef->TextBlock_Dialogue_Select_1->SetVisibility(ESlateVisibility::Hidden);
		DialogueWidgetRef->TextBlock_Dialogue_Select_2->SetVisibility(ESlateVisibility::Hidden);
		DialogueWidgetRef->RichTextBlock_Dialogue->SetVisibility(ESlateVisibility::Hidden);

		if (DialogueWidgetRef->Image_Dialogue_Select_1->Brush.GetResourceName() == "icon_dia_select_yes_32_32") {
			DreamMDreamFragment();
		}
		else if (DialogueWidgetRef->Image_Dialogue_Select_2->Brush.GetResourceName() == "icon_dia_select_yes_32_32") {
			DreamMRandomTalk();
		}

		DialogueWidgetRef->Image_Npc->SetVisibility(ESlateVisibility::Visible);
		DialogueWidgetRef->Overlay_NpcName->SetVisibility(ESlateVisibility::Visible);
		BeforeSelectingDialogue = false;
	}
}

void ADreamM::DreamMStartTalk() {
	if (Peppy->OverlappedActor == this) {
		if (BeforeSelectingDialogue) {
			SelectDialogue();
		}
		else {
			Peppy->InteractionCameraMove(this);

			if (InteractionUI->Image_interaction->Brush.GetResourceName() == "UI_hubworld_talk_v1") {
				BeforeSelectingDialogue = false;
				DreamMRandomTalk();
			}
			else if (InteractionUI->Image_interaction->Brush.GetResourceName() == "UI_hubworld_talk_v2") {
				if (DialogueWidgetClass) {
					DialogueWidgetRef = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
					if (DialogueWidgetRef) {
						DialogueWidgetRef->AddToViewport();
					}
					else {
						NTLOG(Warning, TEXT("BP_Dialogue widget creating is failed!"));
					}
				}

				BeforeSelectingDialogue = true;
				DialogueWidgetRef->Image_Dialogue_Select_1->SetVisibility(ESlateVisibility::Visible);
				DialogueWidgetRef->Image_Dialogue_Select_2->SetVisibility(ESlateVisibility::Visible);
				DialogueWidgetRef->TextBlock_Dialogue_Select_1->SetVisibility(ESlateVisibility::Visible);
				DialogueWidgetRef->TextBlock_Dialogue_Select_2->SetVisibility(ESlateVisibility::Visible);
				DialogueWidgetRef->Image_Npc->SetVisibility(ESlateVisibility::Hidden);
				DialogueWidgetRef->Overlay_NpcName->SetVisibility(ESlateVisibility::Hidden);
				DialogueWidgetRef->Image_CutScene->SetOpacity(0.0);
				SetPeppyName();
			}
			else {
				BeforeSelectingDialogue = false;

				if (DialogueWidgetClass) {
					DialogueWidgetRef = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
					if (DialogueWidgetRef) {
						DialogueWidgetRef->AddToViewport();
					}
					else {
						NTLOG(Warning, TEXT("BP_Dialogue widget creating is failed!"));
					}
				}

				DreamMAfterBattleTalk();
			}
		}
	}
}