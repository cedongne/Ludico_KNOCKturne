// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SpecialSkillIconWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "HUDSpecialSkillHoverWidget.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"
#include "GameInstance/ActorManagerSystem.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void USpecialSkillIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_Active = (UImage*)GetWidgetFromName(TEXT("Image_Active"));
	Image_Opacity60 = (UImage*)GetWidgetFromName(TEXT("Image_Opacity60"));
	TextBlock_Timer = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Timer"));
	TextBlock_SpecialtyKey = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SpecialtyKey"));
}

void USpecialSkillIconWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();
}

void USpecialSkillIconWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	if (HUDSpecialSkillHoverWidget && !Button_Background->IsHovered() && !HUDSpecialSkillHoverWidget->IsHovered()) {
		HUDSpecialSkillHoverWidget->RemoveFromParent();
	}
}

FString USpecialSkillIconWidget::CheckProbability(float Probability)
{
	if (Probability != -1.0) {
		return FString::FromInt(round(Probability * 100.0));
	}
	else {
		return "None";
	}
}

FString USpecialSkillIconWidget::CheckValueN(int SkillIndex, float ValueN)
{
	if (ValueN != -1.0) {
		if (SkillIndex == 72 || SkillIndex == 91) {
			return FString::FromInt(round(ValueN * 100.0));
		}
		else {
			return FString::FromInt(round(ValueN));
		}
	}
	else {
		return "None";
	}
}

FString USpecialSkillIconWidget::CheckValueM(int SkillIndex, float ValueM)
{
	if (ValueM != -1.0) {
		if (SkillIndex == 91) {
			return FString::FromInt(round(ValueM * 100.0));
		}
		else {
			return FString::FromInt(round(ValueM));
		}
	}
	else {
		return "None";
	}
}

FString USpecialSkillIconWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
{
	switch (FCString::Atoi(*Num)) {
	case 0:
		return CheckValueN(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Skill_Index, BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Value1N);
	case 1:
		return CheckValueM(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Skill_Index, BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Value1M);
	case 2:
		return FString::FromInt(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Value1T);
	case 3:
		return CheckProbability(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Probability_1);

	default:
		return "None";
	}
}

FString USpecialSkillIconWidget::RedefineDescription(int RowNum)
{
	FString rowname = BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->SpecialSkillDescript;
	FString OriginalStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			FString tmp1 = Redefined.Mid(0, idx + 1);
			FString skillindex = GetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 1, 1));
			FString tmp2 = Redefined.Mid(idx + 2, Redefined.Len() - (idx + 2));

			Redefined = (tmp1.Append(skillindex)).Append(tmp2);
		}
	}

	for (int index = 0; index < Redefined.Len(); index++) {
		if (Redefined[index] == '{' || Redefined[index] == '}') {
			Redefined.RemoveAt(index, 1);
		}
	}

	return Redefined;
}

void USpecialSkillIconWidget::CreateHoverWidget()
{
	if (HUDSpecialSkillHoverWidgetClass) {
		HUDSpecialSkillHoverWidget = CreateWidget<UHUDSpecialSkillHoverWidget>(GetWorld(), HUDSpecialSkillHoverWidgetClass);
		if (HUDSpecialSkillHoverWidget) {
			HUDSpecialSkillHoverWidget->AddToViewport();
			HUDSpecialSkillHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(HUDSpecialSkillHoverWidget);
			SetHoverWidgetUI(HUDSpecialSkillHoverWidget);
		}
	}
}

void USpecialSkillIconWidget::SetHoverWidgetUI(UHUDSpecialSkillHoverWidget* HoverWidget)
{
	int RowNum = BattleManagerSystem->FindSpecialtyRow(Image_Icon->Brush.GetResourceName().ToString());
	FSpecialSkillTable* CurSpecialSkillTableRow = BattleTableManagerSystem->SpecialSkillTableRows[RowNum];
	FString SpecialSkillId = BattleTableManagerSystem->SpecialSkillTable->GetRowNames()[RowNum].ToString();
	FString Name = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SpecialSkillId.Append("_String")), TEXT(""))->KOR;

	HUDSpecialSkillHoverWidget->RichTextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));
	HUDSpecialSkillHoverWidget->TextBlock_Name->SetText(FText::FromString(Name));
	HUDSpecialSkillHoverWidget->Image_SkillIcon->SetBrushFromTexture(CurSpecialSkillTableRow->SpecialSkillIcon);
	FString RemainTime = FString::Printf(TEXT("쿨타임: %s"), *TextBlock_Timer->GetText().ToString());
	HUDSpecialSkillHoverWidget->TextBlock_RemainTime->SetText(FText::FromString(RemainTime));
}

void USpecialSkillIconWidget::SetHoverWidgetPos(UHUDSpecialSkillHoverWidget* HoverWidget)
{
	FVector2D SpecialSkillIconPixelPos;
	FVector2D SpecialSkillIconViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), SpecialSkillIconPixelPos, SpecialSkillIconViewportPos);

	FVector2D SpecialSkillIconSize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = HUDSpecialSkillHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = SpecialSkillIconViewportPos.X - HoverWidgetSize.X / 2 + SpecialSkillIconSize.X / 2;
	HoverWidgetPos.Y = SpecialSkillIconViewportPos.Y - (HoverWidgetSize.Y + 8);
	UWidgetLayoutLibrary::SlotAsCanvasSlot(HUDSpecialSkillHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}

void USpecialSkillIconWidget::SetCoolTimeText()
{
	int32 CoolTime = ActorManagerSystem->SpecialSkillActor->GetCurSpecialSkillCoolTime();

	TextBlock_Timer->SetText(FText::FromString(FString::FromInt(CoolTime)));

	if (CoolTime == 0) {
		TextBlock_Timer->SetVisibility(ESlateVisibility::Hidden);
		bool CanUseSpecialSkill = ActorManagerSystem->SpecialSkillActor->IsSatisfyUseCondition();

		if (CanUseSpecialSkill) {
			Image_Opacity60->SetVisibility(ESlateVisibility::Hidden);
			Image_Active->SetVisibility(ESlateVisibility::Visible);
			TextBlock_SpecialtyKey->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			Image_Opacity60->SetVisibility(ESlateVisibility::Visible);
			Image_Active->SetVisibility(ESlateVisibility::Hidden);
			TextBlock_SpecialtyKey->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else {
		TextBlock_Timer->SetVisibility(ESlateVisibility::Visible);
		Image_Opacity60->SetVisibility(ESlateVisibility::Visible);
		Image_Active->SetVisibility(ESlateVisibility::Hidden);
		TextBlock_SpecialtyKey->SetVisibility(ESlateVisibility::Hidden);
	}
}
