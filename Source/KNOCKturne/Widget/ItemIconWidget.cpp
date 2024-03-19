// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemIconWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "HUDItemHoverWidget.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UItemIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
}

void UItemIconWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
}

void UItemIconWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	if (HUDItemHoverWidget && !Button_Background->IsHovered() && !HUDItemHoverWidget->IsHovered()) {
		HUDItemHoverWidget->RemoveFromParent();
	}
}

FString UItemIconWidget::CheckValueN(int SkillIndex, float ValueN)
{
	if (ValueN != -1.0) {
		return FString::FromInt(round(ValueN));
	}
	else {
		return "None";
	}
}

FString UItemIconWidget::CheckValueM(int SkillIndex, float ValueM)
{
	if (ValueM != -1.0) {
		return FString::FromInt(round(ValueM * 100));
	}
	else {
		return "None";
	}
}

FString UItemIconWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
{
	switch (FCString::Atoi(*Num)) {
	case 0:
		return CheckValueN(0, BattleTableManagerSystem->ItemTableRows[RowNum]->value1N);
	case 1:
		return CheckValueM(0, BattleTableManagerSystem->ItemTableRows[RowNum]->value1M);
	default:
		return "None";
	}
}

FString UItemIconWidget::RedefineDescription(int RowNum)
{
	FString rowname = BattleTableManagerSystem->ItemTableRows[RowNum]->ItemDescript;
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

void UItemIconWidget::CreateHoverWidget()
{
	if (HUDItemHoverWidgetClass) {
		HUDItemHoverWidget = CreateWidget<UHUDItemHoverWidget>(GetWorld(), HUDItemHoverWidgetClass);
		if (HUDItemHoverWidget) {
			HUDItemHoverWidget->AddToViewport();
			HUDItemHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(HUDItemHoverWidget);
			SetHoverWidgetUI(HUDItemHoverWidget);
		}
	}
}

void UItemIconWidget::SetHoverWidgetUI(UHUDItemHoverWidget* HoverWidget)
{
	int RowNum = BattleManagerSystem->FindItemRow(Image_Icon->Brush.GetResourceName().ToString());
	FItemData* CurItemTableRow = BattleTableManagerSystem->ItemTableRows[RowNum];
	FString ItemId = BattleTableManagerSystem->ItemTable->GetRowNames()[RowNum].ToString();
	FString Name = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*ItemId.Append("_String")), TEXT(""))->KOR;

	HUDItemHoverWidget->RichTextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));
	HUDItemHoverWidget->TextBlock_Name->SetText(FText::FromString(Name));
	HUDItemHoverWidget->Image_SkillIcon->SetBrushFromTexture(CurItemTableRow->ItemIcon);
}

void UItemIconWidget::SetHoverWidgetPos(UHUDItemHoverWidget* HoverWidget)
{
	FVector2D ItemIconPixelPos;
	FVector2D ItemIconViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), ItemIconPixelPos, ItemIconViewportPos);

	FVector2D SpecialSkillIconSize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = HUDItemHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = ItemIconViewportPos.X - HoverWidgetSize.X / 2 + SpecialSkillIconSize.X / 2;
	HoverWidgetPos.Y = ItemIconViewportPos.Y - (HoverWidgetSize.Y + 8);
	UWidgetLayoutLibrary::SlotAsCanvasSlot(HUDItemHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}
