// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

void UDialogueWidget::NativePreConstruct() {
	Image_BlackScreen = (UImage*)GetWidgetFromName(TEXT("Image_BlackScreen"));
	HandCutScene = (UImage*)GetWidgetFromName(TEXT("HandCutScene"));
	Image_Peppy = (UImage*)GetWidgetFromName(TEXT("Image_Peppy"));
	Image_Npc = (UImage*)GetWidgetFromName(TEXT("Image_Npc"));
	Image_CutScene = (UImage*)GetWidgetFromName(TEXT("Image_CutScene"));
	Image_Dialogue = (UImage*)GetWidgetFromName(TEXT("Image_Dialogue"));
	RichTextBlock_Dialogue = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_Dialogue"));
	Image_Continue = (UImage*)GetWidgetFromName(TEXT("Image_Continue"));
	TextBlock_E = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_E"));
	Image_NpcName = (UImage*)GetWidgetFromName(TEXT("Image_NpcName"));
	Text_NpcName = (UTextBlock*)GetWidgetFromName(TEXT("Text_NpcName"));
	Image_PeppyName = (UImage*)GetWidgetFromName(TEXT("Image_PeppyName"));
	Text_PeppyName = (UTextBlock*)GetWidgetFromName(TEXT("Text_PeppyName"));
	Image_Dialogue_Select_1 = (UImage*)GetWidgetFromName(TEXT("Image_Dialogue_Select_1"));
	Image_Dialogue_Select_2 = (UImage*)GetWidgetFromName(TEXT("Image_Dialogue_Select_2"));
	TextBlock_Dialogue_Select_1 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Dialogue_Select_1"));
	TextBlock_Dialogue_Select_2 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Dialogue_Select_2"));
	Overlay_NpcName = (UOverlay*)GetWidgetFromName(TEXT("Overlay_NpcName"));
	Overlay_PeppyName = (UOverlay*)GetWidgetFromName(TEXT("Overlay_PeppyName"));
	PeppyAppear = (UWidgetAnimation*)GetWidgetFromName(TEXT("PeppyAppear"));
	DreamMAppear = (UWidgetAnimation*)GetWidgetFromName(TEXT("DreamMAppear"));
}

void UDialogueWidget::ChangeName(FDialogueData DataRow) {
	FString CurrentCharacterStringID = DataRow.CharacterStringID;

	if (CurrentCharacterStringID == "Peppy_character") {
		Text_PeppyName->SetText(FText::FromString("페피"));
		Overlay_NpcName->SetRenderOpacity(0.0);
		Overlay_PeppyName->SetRenderOpacity(1.0);
	}
	else if (CurrentCharacterStringID == "Unknown_character") {
		Text_NpcName->SetText(FText::FromString("???"));
		Overlay_NpcName->SetRenderOpacity(1.0);
		Overlay_PeppyName->SetRenderOpacity(0.0);
	}
	else if (CurrentCharacterStringID == "DreamM_character") {
		Text_NpcName->SetText(FText::FromString("꿈 관장자"));
		Overlay_NpcName->SetRenderOpacity(1.0);
		Overlay_PeppyName->SetRenderOpacity(0.0);
	}
	else if (CurrentCharacterStringID == "Rabbit_character") {
		Text_NpcName->SetText(FText::FromString("허브월드 토끼"));
		Overlay_NpcName->SetRenderOpacity(1.0);
		Overlay_PeppyName->SetRenderOpacity(0.0);
	}
	else if (CurrentCharacterStringID == "YellowRose_character") {
		Text_NpcName->SetText(FText::FromString("노란 장미"));
		Overlay_NpcName->SetRenderOpacity(1.0);
		Overlay_PeppyName->SetRenderOpacity(0.0);
	}
}

void UDialogueWidget::ChangePeppyImg(FDialogueData DataRow) {
	FString CurrentImageLID = DataRow.ImageLID;

	if (CurrentImageLID == "Im_dia_peppy_basic") {
		Image_Peppy->SetBrushFromTexture(Im_dia_peppy_basic);
		Image_Peppy->SetOpacity(1.0);
	}
	else if (CurrentImageLID == "Im_dia_peppy_shock") {
		Image_Peppy->SetBrushFromTexture(Im_dia_peppy_shock);
		Image_Peppy->SetOpacity(1.0);
	}
	else if (CurrentImageLID == "Im_dia_peppy_noidea") {
		Image_Peppy->SetBrushFromTexture(Im_dia_peppy_noidea);
		Image_Peppy->SetOpacity(1.0);
	}
	else {
		Image_Peppy->SetOpacity(0.0);
	}
}

void UDialogueWidget::ChangeNPCImg(FDialogueData DataRow) {
	FString CurrentImageRID = DataRow.ImageRID;

	if (CurrentImageRID == "Im_dia_dreamM_basic") {
		Image_Npc->SetBrushFromTexture(Im_dia_dreamM_basic);
		Image_Npc->SetOpacity(1.0);
	}
	else if (CurrentImageRID == "Im_dia_dreamM_shock") {
		Image_Npc->SetBrushFromTexture(Im_dia_dreamM_shock);
		Image_Npc->SetOpacity(1.0);
	}
	else if (CurrentImageRID == "Im_dia_dreamM_worry") {
		Image_Npc->SetBrushFromTexture(Im_dia_dreamM_worry);
		Image_Npc->SetOpacity(1.0);
	}
	else if (CurrentImageRID == "Im_dia_dreamM_happy") {
		Image_Npc->SetBrushFromTexture(Im_dia_dreamM_happy);
		Image_Npc->SetOpacity(1.0);
	}
	else if (CurrentImageRID == "Im_dia_dreamM_sadsmile") {
		Image_Npc->SetBrushFromTexture(Im_dia_dreamM_sadsmile);
		Image_Npc->SetOpacity(1.0);
	}
	else if (CurrentImageRID == "Im_dia_yellowrose") {
		Image_Npc->SetBrushFromTexture(Im_dia_yellowrose);
		Image_Npc->SetOpacity(1.0);
	}
	else {
		Image_Npc->SetOpacity(0.0);
	}
}

void UDialogueWidget::ChangeBySpeakType(FDialogueData DataRow) {
	int32 CurrentSpeakType = DataRow.SpeakType;

	if (CurrentSpeakType == 1) {
		PlayAnimation(PeppyAppear);
	}
	else if (CurrentSpeakType == 2) {
		PlayAnimation(DreamMAppear);
	}
	else if (CurrentSpeakType == 3) {
		Image_Peppy->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		Image_Npc->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.f));
	}
	else if (CurrentSpeakType == 4) {
		Image_Peppy->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.f));
		Image_Npc->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void UDialogueWidget::ChangeCutScene(FDialogueData DataRow) {
	FString CurrentCutSID = DataRow.CutSID;

	if (CurrentCutSID == "Im_cutS_pro_hand") {
		Image_CutScene->SetOpacity(0.0);
		HandCutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_lake") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_lake);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dream1") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dream1);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dream2") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dream2);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dream3") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dream3);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dreamW1") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dreamW1);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dreamW2") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dreamW2);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dreamW3") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dreamW3);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dreamW4") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dreamW4);
		Image_CutScene->SetOpacity(1.0);
	}
	else if (CurrentCutSID == "Im_cutS_pro_dreamW5") {
		HandCutScene->SetOpacity(0.0);
		Image_CutScene->SetBrushFromTexture(Im_cutS_pro_dreamW5);
		Image_CutScene->SetOpacity(1.0);
	}
	else {
		Image_CutScene->SetOpacity(0.0);
	}
}

void UDialogueWidget::ChangeDialogueUI(FDialogueData DataRow) {
	ChangeName(DataRow);
	ChangeBySpeakType(DataRow);
	ChangePeppyImg(DataRow);
	ChangeNPCImg(DataRow);
	ChangeCutScene(DataRow);
}