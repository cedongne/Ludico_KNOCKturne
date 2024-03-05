// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/ItemSkillHoverWidget.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "PackageWidget.h"

void UItemSkillHoverWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_Count = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Count"));
}

void UItemSkillHoverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

void UItemSkillHoverWidget::SetHoverWidgetUI(int RowNum, bool IsSelected)
{
	FItemData* ItemData = BattleTableManagerSystem->ItemTableRows[RowNum];
	FString ItemId = BattleTableManagerSystem->ItemTable->GetRowNames()[RowNum].ToString();
	FString NameStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*ItemId.Append("_String")), TEXT(""))->KOR;
	FString DescriptionStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*ItemData->ItemDescript), TEXT(""))->KOR;

	if (IsSelected)
		Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	else
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);

	Image_Icon->SetBrushFromTexture(ItemData->ItemIcon);
	TextBlock_Count->SetText(FText::FromString(FString::FromInt(BattleManagerSystem->ItemCountList[RowNum])));
	TextBlock_SkillName->SetText(FText::FromString(NameStr));
	TextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));
}

FString UItemSkillHoverWidget::CheckValueN(int SkillIndex, float ValueN)
{
	if (ValueN != -1.0) {
		return FString::FromInt(round(ValueN));
	}
	else {
		return "None";
	}
}

FString UItemSkillHoverWidget::CheckValueM(int SkillIndex, float ValueM)
{
	if (ValueM != -1.0) {
		return FString::FromInt(round(ValueM * 100));
	}
	else {
		return "None";
	}
}

FString UItemSkillHoverWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
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

FString UItemSkillHoverWidget::RedefineDescription(int RowNum)
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

void UItemSkillHoverWidget::ClickButton()
{
	int CurItemRowNum = BattleManagerSystem->FindItemRow(Image_Icon->Brush.GetResourceName().ToString());
	int CurItemCount = BattleManagerSystem->ItemCountList[CurItemRowNum];
	if (CurItemCount == 0)
		return;

	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);

		if (PackageWidget)
			PackageWidget->SelectItem(Image_Icon->Brush.GetResourceName().ToString());
	}
	else {
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);

		if (PackageWidget)
			PackageWidget->CancelItem(Image_Icon->Brush.GetResourceName().ToString());
	}
}
