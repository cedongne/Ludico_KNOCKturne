// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DreamFragmentWidget.h"

#include "ItemCardWidget.h"

UDreamFragmentWidget::UDreamFragmentWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
}

void UDreamFragmentWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	Button_Cancel = (UButton*)GetWidgetFromName(TEXT("Button_Cancel"));
	Button_Select = (UButton*)GetWidgetFromName(TEXT("Button_Select"));
	GridPanel = (UGridPanel*)GetWidgetFromName(TEXT("GridPanel"));
}

void UDreamFragmentWidget::NativeConstruct() {
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	if (Button_Select) {
		Button_Select->OnClicked.AddDynamic(this, &UDreamFragmentWidget::Button_SelectOnClicked);
	}

	for (int i = 0; i < 3; i++) {
		if (ItemCardFormClass) {
			ItemCardFormRef = CreateWidget<UItemCardWidget>(GetWorld(), ItemCardFormClass);
			if (ItemCardFormRef) {
				ItemCardArr.Add(ItemCardFormRef);
				GridPanel->AddChildToGrid(ItemCardFormRef, 0, i);
			}
		}
	}

	RndItemRowNumSet.Empty();
	PickRandomItem();
	SetItemCardUI();
}

void UDreamFragmentWidget::PickRandomItem() {
	int RndItemRowNum = rand() % BattleTableManagerSystem->ItemTableRows.Num();

	if (BattleManagerSystem->ItemCountList[RndItemRowNum] < 
		BattleTableManagerSystem->ItemTableRows[RndItemRowNum]->MaxCount) {
		RndItemRowNumSet.Add(RndItemRowNum);
	}
	else {
		PickRandomItem();
	}

	if (RndItemRowNumSet.Num() < 3) {
		PickRandomItem();
	}
}

void UDreamFragmentWidget::SetItemCardUI() {
	int CurItemCardIdx = 0;

	for (auto& RndItemRowElem : RndItemRowNumSet) {
		UTexture2D* icon = BattleTableManagerSystem->ItemTableRows[RndItemRowElem]->ItemIcon;
		ItemCardArr[CurItemCardIdx]->Image_Icon->SetBrushFromTexture(icon);

		FString rowname = BattleTableManagerSystem->ItemTable->GetRowNames()[RndItemRowElem].ToString().Append("_String");
		FString name = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
		ItemCardArr[CurItemCardIdx]->TextBlock_Name->SetText(FText::FromString(name));

		FString description = RedefineDescription(RndItemRowElem);
		ItemCardArr[CurItemCardIdx]->RichTextBlock_Description->SetText(FText::FromString(description));

		FString easteregg = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*BattleTableManagerSystem->ItemTableRows[RndItemRowElem]->ItemEasterEgg), TEXT(""))->KOR;
		ItemCardArr[CurItemCardIdx]->TextBlock_Easteregg->SetText(FText::FromString(easteregg));

		FString eastereggcharacter;
		if (BattleTableManagerSystem->ItemTableRows[RndItemRowElem]->ItemEasterEgg_Character != "-1") {
			eastereggcharacter = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*BattleTableManagerSystem->ItemTableRows[RndItemRowElem]->ItemEasterEgg_Character), TEXT(""))->KOR;
		}
		else {
			eastereggcharacter = "";
		}
		ItemCardArr[CurItemCardIdx]->RichTextBlock_EastereggCharacter->SetText(FText::FromString(eastereggcharacter));
		CurItemCardIdx++;
	}
}

void UDreamFragmentWidget::Button_SelectOnClicked() {
	if (AlertModalClass) {
		AlertModalRef = CreateWidget<UAlertModalWidget>(GetWorld(), AlertModalClass);
		if (AlertModalRef) {
			NoticeSound();
			AlertModalRef->AddToViewport();
		}
	}

	FText selcteditemtext;
	int CurItemCardIdx = 0;

	for (auto& RndItemRowElem : RndItemRowNumSet) {
		if (ItemCardArr[CurItemCardIdx]->Image_SubBackground->Brush.GetResourceName().ToString() == "UI_DreamFragments_SubBackgrund_Selected") {
			selcteditemtext = ItemCardArr[CurItemCardIdx]->TextBlock_Name->GetText();
			SelectedItemNum = RndItemRowElem;
		}
		CurItemCardIdx++;
	}

	AlertModalRef->TextBlock_ItemName->SetText(selcteditemtext);
	AlertModalRef->TextBlock_Skip->SetVisibility(ESlateVisibility::Hidden);
	AlertModalRef->TextBlock_ItemName->SetVisibility(ESlateVisibility::Visible);
	AlertModalRef->TextBlock_SelectOrNot->SetVisibility(ESlateVisibility::Visible);

	if (AlertModalRef) {
		AlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UDreamFragmentWidget::OnClicked_AlertModal_Yes);
		AlertModalRef->Button_No->OnClicked.AddDynamic(this, &UDreamFragmentWidget::OnClicked_AlertModal_No);
	}
}

void UDreamFragmentWidget::OnClicked_AlertModal_Yes() {
	BattleManagerSystem->ItemCountList[SelectedItemNum]++;
	AlertModalRef->RemoveFromParent();
	this->RemoveFromParent();
	BattleManagerSystem->DreamFragmentCount--;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, DialogueWidgetArr, DialogueWidgetClass);
	if (DialogueWidgetArr.Num() > 0) {
		UDialogueWidget* DialogueWidget = (UDialogueWidget*)DialogueWidgetArr[0];
		DialogueWidget->isCameraMoving = false;

		CallDreamFragmentTalk();
	}
	else {
		NTLOG(Warning, TEXT("No DialogueWidget!"));
	}

	SelectSound();
}

void UDreamFragmentWidget::OnClicked_AlertModal_No() {
	AlertModalRef->RemoveFromParent();
	CancelSound();
}

FString UDreamFragmentWidget::CheckValueN(int SkillIndex, float ValueN)
{
	if (ValueN != -1.0) {
		return FString::FromInt(round(ValueN));
	}
	else {
		return "None";
	}
}

FString UDreamFragmentWidget::CheckValueM(int SkillIndex, float ValueM)
{
	if (ValueM != -1.0) {
		return FString::FromInt(round(ValueM * 100));
	}
	else {
		return "None";
	}
}

FString UDreamFragmentWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
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

FString UDreamFragmentWidget::RedefineDescription(int RowNum)
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

	int count = -1;
	for (int index = 0; index < Redefined.Len(); index++) {
		if (Redefined[index] == '{' || Redefined[index] == '}') {
			count++;
			Redefined.RemoveAt(index, 1);
		}
	}

	return Redefined;
}
