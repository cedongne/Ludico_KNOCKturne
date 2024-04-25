// Fill out your copyright notice in the Description page of Project Settings.


#include "AndYouWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include <Kismet/GameplayStatics.h>
#include "GameInstance/BattleManagerSystem.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UAndYouWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	TextBlock_BattleClearTime = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_BattleClearTime"));
	TextBlock_PlayTime = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_PlayTime"));
	TextBlock_TryBattleCount = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_TryBattleCount"));
	UniformGridPanel_Skill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Skill"));
	Image_SpecialSkill = (UImage*)GetWidgetFromName(TEXT("Image_SpecialSkill"));
	Image_Item = (UImage*)GetWidgetFromName(TEXT("Image_Item"));
}

void UAndYouWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();

	SetBattleClearTime();
	SetTryBattleCountText();
	SetSelectedSkills();
	SetPlayTime();
}

void UAndYouWidget::SetBattleClearTime()
{
	FString ClearTime;
	int Hour = BattleManagerSystem->BattleClearTime.GetHours();
	int Minute = BattleManagerSystem->BattleClearTime.GetMinutes();
	int Second = BattleManagerSystem->BattleClearTime.GetSeconds();

	if (Hour < 10) {
		ClearTime = "0" + FString::FromInt(Hour) + ":";
	}
	else {
		ClearTime = FString::FromInt(Hour) + ":";
	}

	if (Minute < 10) {
		ClearTime += "0" + FString::FromInt(Minute) + ":";
	}
	else {
		ClearTime += FString::FromInt(Minute) + ":";
	}

	if (Second < 10) {
		ClearTime += "0" + FString::FromInt(Second);
	}
	else {
		ClearTime += FString::FromInt(Second);
	}

	TextBlock_BattleClearTime->SetText(FText::FromString(ClearTime));
}

void UAndYouWidget::SetTryBattleCountText()
{
	int TryBattle = BattleManagerSystem->TryBattleCount;
	if (TryBattle < 10) {
		FString TryBattleStr = "0" + FString::FromInt(TryBattle);
		TextBlock_TryBattleCount->SetText(FText::FromString(TryBattleStr));
	}
	else {
		TextBlock_TryBattleCount->SetText(FText::FromString(FString::FromInt(TryBattle)));
	}
}

void UAndYouWidget::SetSelectedSkills()
{
	for (int i = 0; i < BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
		UImage* SkillImg = (UImage*)UniformGridPanel_Skill->GetChildAt(i);
		SkillImg->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[i]->SkillIcon);
	}

	for (int i = BattleManagerSystem->SelectedSkillCodeList.Num(); i < 8; i++) {
		UImage* SkillImg = (UImage*)UniformGridPanel_Skill->GetChildAt(i);
		SkillImg->SetVisibility(ESlateVisibility::Hidden);
	}

	UTexture2D* SpecialSkillImg = BattleTableManagerSystem->SpecialSkillTable->FindRow<FSpecialSkillTable>(FName(*BattleManagerSystem->FinalSpecialSkill), TEXT(""))->SpecialSkillIcon;
	if (BattleManagerSystem->SelectedSkillCodeList.Num() <= 4) {
		UImage* SpecialSkill = (UImage*)UniformGridPanel_Skill->GetChildAt(4);
		SpecialSkill->SetBrushFromTexture(SpecialSkillImg);
		SpecialSkill->SetVisibility(ESlateVisibility::Visible);

		UImage* Item = (UImage*)UniformGridPanel_Skill->GetChildAt(5);
		if (BattleManagerSystem->FinalItem != "") {
			UTexture2D* ItemImg = BattleTableManagerSystem->ItemTable->FindRow<FItemData>(FName(*BattleManagerSystem->FinalItem), TEXT(""))->ItemIcon;
			Item->SetBrushFromTexture(ItemImg);
			Item->SetVisibility(ESlateVisibility::Visible);
		}

		Image_SpecialSkill->SetVisibility(ESlateVisibility::Hidden);
		Image_Item->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		Image_SpecialSkill->SetBrushFromTexture(SpecialSkillImg);
		if (BattleManagerSystem->FinalItem != "") {
			UTexture2D* ItemImg = BattleTableManagerSystem->ItemTable->FindRow<FItemData>(FName(*BattleManagerSystem->FinalItem), TEXT(""))->ItemIcon;
			Image_Item->SetBrushFromTexture(ItemImg);
		}
		else {
			Image_Item->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UAndYouWidget::SetPlayTime()
{
	FString PlayTime;
	int Hour = BattleManagerSystem->TotalPlayTime.GetHours();
	int Minute = BattleManagerSystem->TotalPlayTime.GetMinutes();
	int Second = BattleManagerSystem->TotalPlayTime.GetSeconds();

	if (Hour < 10) {
		PlayTime = "0" + FString::FromInt(Hour) + ":";
	}
	else {
		PlayTime = FString::FromInt(Hour) + ":";
	}

	if (Minute < 10) {
		PlayTime += "0" + FString::FromInt(Minute) + ":";
	}
	else {
		PlayTime += FString::FromInt(Minute) + ":";
	}

	if (Second < 10) {
		PlayTime += "0" + FString::FromInt(Second);
	}
	else {
		PlayTime += FString::FromInt(Second);
	}

	TextBlock_PlayTime->SetText(FText::FromString(PlayTime));
}
