// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

void UDialogueWidget::NativeOnInitialized() {
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

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

/*void UDialogueWidget::ChangeName(FDialogueData DataRow) {
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
}*/

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

void UDialogueWidget::DownArrowEvent() {
	/*UTexture2D* Texture = Cast<UTexture2D>(Image_Dialogue_Select_1->Brush.GetResourceObject());

	if (Image_Dialogue_Select_1->GetVisibility() == ESlateVisibility::Visible) {
		if (Texture == icon_dia_select_yes_32_32) {
			Image_Dialogue_Select_1->SetBrushFromTexture(icon_dia_select_no_32_32);
			TextBlock_Dialogue_Select_1->SetColorAndOpacity(FLinearColor(0.623961f, 0.623961f, 0.623961f, 1.f));
			Image_Dialogue_Select_2->SetBrushFromTexture(icon_dia_select_yes_32_32);
			TextBlock_Dialogue_Select_2->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));
		}
	}*/
}

void UDialogueWidget::UpArrowEvent() {
	/*UTexture2D* Texture = Cast<UTexture2D>(Image_Dialogue_Select_2->Brush.GetResourceObject());

	if (Image_Dialogue_Select_2->GetVisibility() == ESlateVisibility::Visible) {
		if (Texture == icon_dia_select_yes_32_32) {
			Image_Dialogue_Select_1->SetBrushFromTexture(icon_dia_select_yes_32_32);
			TextBlock_Dialogue_Select_1->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));
			Image_Dialogue_Select_2->SetBrushFromTexture(icon_dia_select_no_32_32);
			TextBlock_Dialogue_Select_2->SetColorAndOpacity(FLinearColor(0.623961f, 0.623961f, 0.623961f, 1.f));
		}
	}*/
}

FString UDialogueWidget::GetSkillIndexByKeyword(FString Num) {
	switch(FCString::Atoi(*Num)) {
		case 0:
			return FString::FromInt(BattleManagerSystem->Round);
		case 1:
			return FString::FromInt(100 - BattleManagerSystem->LastRoundBossHpRatio);
		default:
			return "None";
	}
}

FString UDialogueWidget::GetValueOfSkillIndex(FString Description, int32 OpenBracesArrayIndex) {
	int32 index = OpenBracesArray[OpenBracesArrayIndex];
	FString substr = Description.Mid(index + 2, index + 3);
	if (substr == "}") {
		CloseBracesIndex = index + 2;
		FString SkillIndexStr = GetSkillIndexByKeyword(Description.Mid(index + 1, index + 2));

		return SkillIndexStr;
	}
	else {
		CloseBracesIndex = index + 3;
		FString SkillIndexStr = GetSkillIndexByKeyword(Description.Mid(index + 1, index + 3));

		return SkillIndexStr;
	}
}

FString UDialogueWidget::RedefineLine(FString Description) {
	for (int index = 0; index < Description.Len(); index++) {
		if (Description.Mid(index, index + 1) == "{") {
			SkillIndexValueArrayIndex++;
			OpenBracesArray.SetNum(OpenBracesArray.Num() + 1);
			OpenBracesArray[SkillIndexValueArrayIndex] = index;
		}
	}

	for (int idx = 0; idx < OpenBracesArray.Num(); idx++) {
		FString str1 = GetValueOfSkillIndex(Description, idx);
		if (idx == 0) {
			FString str2 = Description.Mid(0, OpenBracesArray[idx]);
			FString str3 = str2.Append(str1);
			int temp_idx = CloseBracesIndex + 1;
			FString str4 = Description.Mid(temp_idx, (OpenBracesArray[idx + 1] - temp_idx) + temp_idx);

			if (idx + 1 < OpenBracesArray.Num()) {
				RedefinedDescription = str3.Append(str4);
			}
			else {
				RedefinedDescription = str3;
			}
		}
		else {
			FString str2 = RedefinedDescription.Append(str1);
			int temp_idx = CloseBracesIndex + 1;
			FString str3 = Description.Mid(temp_idx, (OpenBracesArray[idx + 1] - temp_idx) + temp_idx);

			if (idx + 1 < OpenBracesArray.Num()) {
				RedefinedDescription = str2.Append(str3);
			}
			else {
				RedefinedDescription = str2;
			}
		}
	}
	int temp_idx = CloseBracesIndex + 1;
	int temp_idx2 = Description.Len() - 1 - CloseBracesIndex;
	RedefinedDescription = RedefinedDescription.Append(Description.Mid(temp_idx, temp_idx + temp_idx2));
	return RedefinedDescription;
}

FString UDialogueWidget::ApplyRedefinedLine(FString OriginalStr, UDialogueTableComponent* DialogueTableComponentRowVar) {
	int32 index = DialogueTableComponentRowVar->GetCurrentRow();
	FName RowName = DialogueTableComponentRowVar->DialogueTable->GetRowNames()[index];
	bool isRedefineNeeded = DialogueTableComponentRowVar->isRedefineNeededLine(RowName.ToString());

	if (isRedefineNeeded) {
		return RedefineLine(OriginalStr);
	}
	else {
		return OriginalStr;
	}
}

void UDialogueWidget::NextTalk(UDialogueTableComponent* DialogueTableComponentRowVar) {
	TextSpeed = 0.07;
	FDialogueData dialogueData = DialogueTableComponentRowVar->GetNextRowDialogueTable();
	FString originalDialogue = DialogueTableComponentRowVar->GetStringOnBP(dialogueData);
	FString Line = ApplyRedefinedLine(originalDialogue, DialogueTableComponentRowVar);
	FullDialogue = Line;
	TypingEffect();
	ChangeDialogueUI(dialogueData);

	if (dialogueData.Direction == "-1") {
		isDirection = false;
	}
	else {
		isDirection = true;
	}

	if (DialogueTableComponentRowVar->NextDialogueTypeIs1()) {
		DialogueTableComponentRowVar->SetIsEndedDialogueRows(true);
	}
}

void UDialogueWidget::InputEDuringTalking(UDialogueTableComponent* DialogueTableComponentRowVar) {
	if (!isCameraMoving) {
		if (InputEDuringWriting) {
			TextSpeed = 0.005;
		}
		else {
			if (DialogueTableComponentRowVar->IsEndedDialogueRows)
			{
				IsEndedDialogueRowsTrue();

				PeppyController = (APeppyController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
				PeppyController->CanInteraction = true;
			}
			else {
				if (isDirection) {
					IsDirectionTrue();
				}
				else {
					NextTalk(DialogueTableComponentRowVar);
				}
			}
		}
	}
}

void UDialogueWidget::AfterBattleFailDirection(FDialogueData DataRow, UDialogueTableComponent* DialogueTableComponentVar) {
	if (DataRow.Direction == "AfterBattleFail_Hubworld_DreamDiary") {
		if (KNOCKturneGameState->isDreamDiaryUpdated) {
			DialogueTableComponentVar->SetBattleFailDiaryDialogueIndex();
		}
		else {
			DialogueTableComponentVar->SetIsEndedDialogueRows(true);
		}
	}
	else {
		if (DataRow.Direction == "AfterBattleFail_Hubworld_DreamFragment") {
			if (KNOCKturneGameState->GetDreamFragment) {
				DialogueTableComponentVar->SetBattleFailFragmentDialogueIndex();
			}
			else {
				DialogueTableComponentVar->SetIsEndedDialogueRows(true);
			}
		}
	}
}