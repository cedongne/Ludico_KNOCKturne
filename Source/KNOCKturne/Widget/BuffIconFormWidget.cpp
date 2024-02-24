// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BuffIconFormWidget.h"
#include <Kismet/GameplayStatics.h>
#include "GameInstance/ActorManagerSystem.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "BuffHoverWidget.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UBuffIconFormWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	ProgressBar_Term = (UProgressBar*)GetWidgetFromName(TEXT("ProgressBar_Term"));
}

void UBuffIconFormWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = GameInstance->GetSubsystem<UActorManagerSystem>();

	if (Button_Background) {
		Button_Background->OnHovered.AddDynamic(this, &UBuffIconFormWidget::CreateHoverWidget);
	}
}

void UBuffIconFormWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	if (CurBuffHoverWidget && !IsHovered() && !CurBuffHoverWidget->IsHovered()) {
		CurBuffHoverWidget->RemoveFromParent();
	}

	SetProgressBarTerm();
}

FString UBuffIconFormWidget::GetSkillIndexByKeyword(EBuffType BuffType, FString Num)
{
	FBuffData BuffData;
	if (ActorManagerSystem->PeppyActor->BuffComponent->HasBuff(BuffType)) {
		BuffData = ActorManagerSystem->PeppyActor->BuffComponent->GetBuffData(BuffType);
	}
	else if (ActorManagerSystem->BossActor->BuffComponent->HasBuff(BuffType)) {
		BuffData = ActorManagerSystem->BossActor->BuffComponent->GetBuffData(BuffType);
	}
	else {
		return "None";
	}

	if(BuffType == EBuffType::SpeedDecrease)
		return FString::SanitizeFloat(BuffData.Value_N);

	switch (FCString::Atoi(*Num)) {
	case 0:
		return FString::FromInt(BuffData.Value_N);
	case 1:
		return FString::FromInt(BuffData.Value_M);
	case 2:
		return FString::FromInt(BuffData.Value_T);
	default:
		return "None";
	}
}

FString UBuffIconFormWidget::RedefineDescription(int RowNum)
{
	FString rowname = ActorManagerSystem->PeppyActor->BuffComponent->BuffTableRows[RowNum]->BuffDescript;
	FString OriginalStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;
	FString tmp1 = "";
	FString skillindex = "";
	FString tmp2 = "";
	EBuffType BuffType = ActorManagerSystem->PeppyActor->BuffComponent->BuffIconNameToBuffTypeMap[Image_Icon->Brush.GetResourceName().ToString()];

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			if (Redefined[idx + 2] == '}') {
				tmp1 = Redefined.Mid(0, idx + 1);
				skillindex = GetSkillIndexByKeyword(BuffType, Redefined.Mid(idx + 1, 1));
				tmp2 = Redefined.Mid(idx + 2, Redefined.Len() - (idx + 2));
			}
			else {
				tmp1 = Redefined.Mid(0, idx + 2);
				skillindex = GetSkillIndexByKeyword(BuffType, Redefined.Mid(idx + 2, 1));
				tmp2 = Redefined.Mid(idx + 3, Redefined.Len() - (idx + 3));
			}

			Redefined = (tmp1.Append(skillindex)).Append(tmp2);
		}
	}

	int count = -1;
	for (int index = 0; index < Redefined.Len(); index++) {
		if (Redefined[index] == '{' || Redefined[index] == '}') {
			count++;
			Redefined.RemoveAt(index, 1);
		}
	}

	return Redefined;
}

void UBuffIconFormWidget::CreateHoverWidget()
{
	class UBuffHoverWidget* BuffHoverWidget;
	if (BuffHoverWidgetClass) {
		BuffHoverWidget = CreateWidget<UBuffHoverWidget>(GetWorld(), BuffHoverWidgetClass);
		if (BuffHoverWidget) {
			BuffHoverWidget->AddToViewport();
			BuffHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(BuffHoverWidget);
			SetHoverWidgetUI(BuffHoverWidget);
			SetHoverBackgroundAngle(BuffHoverWidget);
			CurBuffHoverWidget = BuffHoverWidget;
		}
	}
}

void UBuffIconFormWidget::SetHoverWidgetUI(UBuffHoverWidget* BuffHoverWidget)
{
	int RowNum = ActorManagerSystem->PeppyActor->BuffComponent->BuffIconNameToRowNum(Image_Icon->Brush.GetResourceName().ToString());
	FBuffTable* BuffTable = ActorManagerSystem->PeppyActor->BuffComponent->BuffTableRows[RowNum];
	FString Name = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*BuffTable->BuffName), TEXT(""))->KOR;

	BuffHoverWidget->RichTextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));
	BuffHoverWidget->TextBlock_Name->SetText(FText::FromString(Name));
	BuffHoverWidget->Image_SkillIcon->SetBrushFromTexture(BuffTable->BuffIcon);

	if (IsPeppyBuff && ActorManagerSystem->PeppyActor->BuffComponent->isTermTypeTurn(CurBuffType)) {
		BuffHoverWidget->SetVisibility(ESlateVisibility::Visible);
		FString RemainTurn = FString::Printf(TEXT("남은 턴: %d턴"), ActorManagerSystem->PeppyActor->BuffComponent->GetRemainTime(CurBuffType));
		BuffHoverWidget->TextBlock_RemainTurn->SetText(FText::FromString(RemainTurn));
	}
	else if (!IsPeppyBuff && ActorManagerSystem->BossActor->BuffComponent->isTermTypeTurn(CurBuffType)) {
		BuffHoverWidget->SetVisibility(ESlateVisibility::Visible);
		FString RemainTurn = FString::Printf(TEXT("남은 턴: %d턴"), ActorManagerSystem->BossActor->BuffComponent->GetRemainTime(CurBuffType));
		BuffHoverWidget->TextBlock_RemainTurn->SetText(FText::FromString(RemainTurn));
	}
	else {
		BuffHoverWidget->TextBlock_RemainTurn->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UBuffIconFormWidget::SetHoverWidgetPos(UBuffHoverWidget* BuffHoverWidget)
{
	FVector2D BuffIconPixelPos;
	FVector2D BuffIconViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), BuffIconPixelPos, BuffIconViewportPos);

	FVector2D BuffIconSize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = BuffHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = BuffIconViewportPos.X - HoverWidgetSize.X / 2 + BuffIconSize.X / 2;
	if (IsPeppyBuff) {
		HoverWidgetPos.Y = BuffIconViewportPos.Y - (HoverWidgetSize.Y + 8);
	}
	else {
		HoverWidgetPos.Y = BuffIconViewportPos.Y + (HoverWidgetSize.Y / 2 - 8);
	}
	UWidgetLayoutLibrary::SlotAsCanvasSlot(BuffHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}

void UBuffIconFormWidget::SetHoverBackgroundAngle(UBuffHoverWidget* BuffHoverWidget)
{
	if (IsPeppyBuff)
		return;

	BuffHoverWidget->Image_Background->SetRenderTransformAngle(180);
	UWidgetLayoutLibrary::SlotAsCanvasSlot(BuffHoverWidget->Image_Background)->SetPosition(FVector2D(-137, -110));
	UWidgetLayoutLibrary::SlotAsCanvasSlot(BuffHoverWidget->Button_Background)->SetPosition(FVector2D(-137, -110));
}

void UBuffIconFormWidget::SetProgressBarTerm()
{
	float OriginalDuration;
	float RemainTime = ActorManagerSystem->PeppyActor->BuffComponent->GetRemainTime(CurBuffType);
	if (IsPeppyBuff && ActorManagerSystem->PeppyActor->BuffComponent->OriginalDuration.Find(CurBuffType)) {
		OriginalDuration = *ActorManagerSystem->PeppyActor->BuffComponent->OriginalDuration.Find(CurBuffType);
		float Percent = (OriginalDuration - RemainTime) / OriginalDuration;
		ProgressBar_Term->SetPercent(Percent);
	}
	else if (!IsPeppyBuff && ActorManagerSystem->BossActor->BuffComponent->OriginalDuration.Find(CurBuffType)) {
		OriginalDuration = *ActorManagerSystem->BossActor->BuffComponent->OriginalDuration.Find(CurBuffType);
		float Percent = (OriginalDuration - RemainTime) / OriginalDuration;
		ProgressBar_Term->SetPercent(Percent);
	}
	else
		NTLOG(Warning, TEXT("Can't SetProgressBarTerm!"));
}
