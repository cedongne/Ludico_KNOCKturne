// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageWidget.h"
#include "Widget/AlertModalWidget.h"
#include <Kismet/GameplayStatics.h>
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"
#include "PackageSkillCardWidget.h"
#include "SpecialSkillCardWidget.h"
#include "ItemSkillCardWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include <GameInstance/DialogueManagerSystem.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PackageSelectedUIWidget.h"

void UPackageWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UniformGridPanel_Skill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Skill"));
	UniformGridPanel_Specialty = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Specialty"));
	UniformGridPanel_Item = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Item"));
	SkillTab = (UButton*)GetWidgetFromName(TEXT("SkillTab"));
	SpecialtyTab = (UButton*)GetWidgetFromName(TEXT("SpecialtyTab"));
	ItemTab = (UButton*)GetWidgetFromName(TEXT("ItemTab"));
	Button_Exit = (UButton*)GetWidgetFromName(TEXT("Button_Exit"));
	Button_Reset = (UButton*)GetWidgetFromName(TEXT("Button_Reset"));
	ScrollBox_Skill = (UScrollBox*)GetWidgetFromName(TEXT("ScrollBox_Skill"));
	Button_SettingDone = (UButton*)GetWidgetFromName(TEXT("Button_SettingDone"));
	UniformGridPanel_SelectedSkill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_SelectedSkill"));
	Selected_Specialty = (UPackageSelectedUIWidget*)GetWidgetFromName(TEXT("Selected_Specialty"));
	Selected_Item = (UPackageSelectedUIWidget*)GetWidgetFromName(TEXT("Selected_Item"));
}

void UPackageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	SelectedSkillIconName.Empty();

	// 특수기 UI 비저빌리티 설정
	Selected_Specialty->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
	Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Visible);

	Selected_Specialty->SelectedSkillType = ESelectedSkillType::SpecialSkill;
	Selected_Item->SelectedSkillType = ESelectedSkillType::Item;

	// 스킬, 특수기, 아이템 리스트 생성
	CreateSkillList();
	CreateSpecialtyList();
	CreateItemList();
	// 선택한 스킬 칸 리스트 UI 생성
	CreateSelectedSkillList();
	// 이전 전투 세팅 기록이 있으면 불러온다
	LoadBeforeSelectedSkills();

	if (SkillTab) {
		SkillTab->OnClicked.AddDynamic(this, &UPackageWidget::ClickSkillTab);
	}
	if (SpecialtyTab) {
		SpecialtyTab->OnClicked.AddDynamic(this, &UPackageWidget::ClickSpecialtyTab);
	}
	if (ItemTab) {
		ItemTab->OnClicked.AddDynamic(this, &UPackageWidget::ClickItemTab);
	}
	if (Button_Exit) {
		Button_Exit->OnClicked.AddDynamic(this, &UPackageWidget::Exit);
	}
	if (Button_Reset) {
		Button_Reset->OnClicked.AddDynamic(this, &UPackageWidget::ResetSetting);
	}
	if (Button_SettingDone) {
		Button_SettingDone->OnClicked.AddDynamic(this, &UPackageWidget::ClickSettingDone);
	}
}

void UPackageWidget::CreateSkillList()
{
	int row = 0;

	for (int i = 0; i < 14; i++) {
		if (PackageSkillCardWidgetClass) {
			UPackageSkillCardWidget* PackageSkillCardWidget = CreateWidget<UPackageSkillCardWidget>(GetWorld(), PackageSkillCardWidgetClass);
			if (PackageSkillCardWidget) {
				SkillListArr.Add(PackageSkillCardWidget);
				if (i % 2 == 1) {
					UniformGridPanel_Skill->AddChildToUniformGrid(PackageSkillCardWidget, row, 1);
					++row;
				}
				else {
					UniformGridPanel_Skill->AddChildToUniformGrid(PackageSkillCardWidget, row, 0);
				}

				SetSkillUI(PackageSkillCardWidget, i);
			}
		}
	}
}

void UPackageWidget::SetSkillUI(UPackageSkillCardWidget* PackageSkillCardWidget, int RowNum)
{
	UTexture2D* Icon = BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIcon;
	PackageSkillCardWidget->Image_Icon->SetBrushFromTexture(Icon);

	FString SkillId = *(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillId);
	FString SkillName = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SkillId.Append("_String")), TEXT(""))->KOR;
	PackageSkillCardWidget->TextBlock_SkillName->SetText(FText::FromString(SkillName));

	FString Stance = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillStance)), TEXT(""))->KOR;
	PackageSkillCardWidget->TextBlock_Stance->SetText(FText::FromString(Stance));

	FString CoolTime = FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillCoolTurn);
	PackageSkillCardWidget->TextBlock_CoolTimeSec->SetText(FText::FromString(CoolTime));

	FString Energy = FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Cost);
	PackageSkillCardWidget->TextBlock_Energy->SetText(FText::FromString(Energy));
}

void UPackageWidget::CreateSpecialtyList()
{
	int row = 0;

	for (int i = 0; i < 8; i++) {
		if (i == 5 || i == 7) {
			if (BP_BlankSpaceClass) {
				UUserWidget* BP_BlankSpaceRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlankSpaceClass);
				if (BP_BlankSpaceRef) {
					UniformGridPanel_Specialty->AddChildToUniformGrid(BP_BlankSpaceRef, row, 1);
					++row;
				}
			}
		}
		else {
			if (SpecialSkillCardWigetClass) {
				USpecialSkillCardWidget* SpecialtyListFormRef = CreateWidget<USpecialSkillCardWidget>(GetWorld(), SpecialSkillCardWigetClass);
				if (SpecialtyListFormRef) {
					SpecialtyListArr.Add(SpecialtyListFormRef);
					if (i % 2 == 1) {
						UniformGridPanel_Specialty->AddChildToUniformGrid(SpecialtyListFormRef, row, 1);
						++row;
					}
					else {
						UniformGridPanel_Specialty->AddChildToUniformGrid(SpecialtyListFormRef, row, 0);
					}

					if (i == 6) {
						SetSpecialtyUI(SpecialtyListFormRef, 5);
					}
					else {
						SetSpecialtyUI(SpecialtyListFormRef, i);
					}
				}
			}
		}
	}
}

void UPackageWidget::SetSpecialtyUI(USpecialSkillCardWidget* SpecialtyListForm, int RowNum)
{
	UTexture2D* Icon = BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->SpecialSkillIcon;
	SpecialtyListForm->Image_Icon->SetBrushFromTexture(Icon);

	FString SpecialSkillId = BattleTableManagerSystem->SpecialSkillTable->GetRowNames()[RowNum].ToString();
	FString SpecialSkillName = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SpecialSkillId.Append("_String")), TEXT(""))->KOR;
	SpecialtyListForm->TextBlock_SkillName->SetText(FText::FromString(SpecialSkillName));

	FString CoolTime = FString::FromInt(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->CoolTime);
	SpecialtyListForm->TextBlock_CoolTimeSec->SetText(FText::FromString(CoolTime));

	FString Energy = FString::FromInt(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->EnergyCost);
	SpecialtyListForm->TextBlock_Energy->SetText(FText::FromString(Energy));
}

void UPackageWidget::CreateItemList()
{
	int row = 0;

	for (int i = 0; i < 8; i++) {
		if (i == 5 || i == 7) {
			if (BP_BlankSpaceClass) {
				UUserWidget* BP_BlankSpaceRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlankSpaceClass);
				if (BP_BlankSpaceRef) {
					UniformGridPanel_Item->AddChildToUniformGrid(BP_BlankSpaceRef, row, 1);
					++row;
				}
			}
		}
		else {
			if (ItemSkillCardWidgetClass) {
				UItemSkillCardWidget* ItemListFormRef = CreateWidget<UItemSkillCardWidget>(GetWorld(), ItemSkillCardWidgetClass);
				if (ItemListFormRef) {
					ItemListArr.Add(ItemListFormRef);
					if (i % 2 == 1) {
						UniformGridPanel_Item->AddChildToUniformGrid(ItemListFormRef, row, 1);
						++row;
					}
					else {
						UniformGridPanel_Item->AddChildToUniformGrid(ItemListFormRef, row, 0);
					}

					if (i == 6) {
						SetItemUI(ItemListFormRef, 5);
					}
					else {
						SetItemUI(ItemListFormRef, i);
					}
				}
			}
		}
	}
}

void UPackageWidget::SetItemUI(UItemSkillCardWidget* ItemListForm, int RowNum)
{
	UTexture2D* Icon = BattleTableManagerSystem->ItemTableRows[RowNum]->ItemIcon;
	ItemListForm->Image_Icon->SetBrushFromTexture(Icon);

	FString ItemId = BattleTableManagerSystem->ItemTable->GetRowNames()[RowNum].ToString();
	FString ItemName = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*ItemId.Append("_String")), TEXT(""))->KOR;
	ItemListForm->TextBlock_SkillName->SetText(FText::FromString(ItemName));

	FString Count = FString::FromInt(KNOCKturneGameState->ItemCountList[RowNum]);
	ItemListForm->TextBlock_Count->SetText(FText::FromString(Count));
}

void UPackageWidget::CreateSelectedSkillList()
{
	int row = 0;

	for (int i = 0; i < 8; i++) {
		if (SelectedUIClass) {
			UPackageSelectedUIWidget* SelectedUIRef = CreateWidget<UPackageSelectedUIWidget>(GetWorld(), SelectedUIClass);
			if (SelectedUIRef) {
				SelectedUIListArr.Add(SelectedUIRef);
				if (i % 2 == 1) {
					UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, row, 0);
				}
				SelectedUIRef->SelectedSkillType = ESelectedSkillType::Skill;
			}
		}
	}
}

void UPackageWidget::ClickSkillTab()
{
	if (SkillTab->WidgetStyle.Normal.GetResourceName() == "UI_beforeBattle_SkillSettingPanel_tab_skill_default") {
		UniformGridPanel_Specialty->SetVisibility(ESlateVisibility::Hidden);
		UniformGridPanel_Specialty->SetIsEnabled(false);

		UniformGridPanel_Item->SetVisibility(ESlateVisibility::Hidden);
		UniformGridPanel_Item->SetIsEnabled(false);

		ScrollBox_Skill->SetVisibility(ESlateVisibility::Visible);
		ScrollBox_Skill->SetIsEnabled(true);

		UniformGridPanel_Skill->SetVisibility(ESlateVisibility::Visible);
		UniformGridPanel_Skill->SetIsEnabled(true);

		SkillTabStyle(true);
		SpecialtyTabStyle(false);
		ItemTabStyle(false);
	}
}

void UPackageWidget::ClickSpecialtyTab()
{
	if (SpecialtyTab->WidgetStyle.Normal.GetResourceName() == "UI_beforeBattle_SkillSettingPanel_tab_specialty_default") {
		UniformGridPanel_Specialty->SetVisibility(ESlateVisibility::Visible);
		UniformGridPanel_Specialty->SetIsEnabled(true);

		UniformGridPanel_Item->SetVisibility(ESlateVisibility::Hidden);
		UniformGridPanel_Item->SetIsEnabled(false);

		ScrollBox_Skill->SetVisibility(ESlateVisibility::Hidden);
		ScrollBox_Skill->SetIsEnabled(false);

		UniformGridPanel_Skill->SetVisibility(ESlateVisibility::Hidden);
		UniformGridPanel_Skill->SetIsEnabled(false);

		SkillTabStyle(false);
		SpecialtyTabStyle(true);
		ItemTabStyle(false);
	}
}

void UPackageWidget::ClickItemTab()
{
	if (ItemTab->WidgetStyle.Normal.GetResourceName() == "UI_beforeBattle_SkillSettingPanel_tab_item_default") {
		UniformGridPanel_Specialty->SetVisibility(ESlateVisibility::Hidden);
		UniformGridPanel_Specialty->SetIsEnabled(false);

		UniformGridPanel_Item->SetVisibility(ESlateVisibility::Visible);
		UniformGridPanel_Item->SetIsEnabled(true);

		ScrollBox_Skill->SetVisibility(ESlateVisibility::Hidden);
		ScrollBox_Skill->SetIsEnabled(false);

		UniformGridPanel_Skill->SetVisibility(ESlateVisibility::Hidden);
		UniformGridPanel_Skill->SetIsEnabled(false);

		SkillTabStyle(false);
		SpecialtyTabStyle(false);
		ItemTabStyle(true);
	}
}

void UPackageWidget::SkillTabStyle(bool Clicked)
{
	if (Clicked) {
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SkillTab->WidgetStyle.Normal, UI_beforeBattle_skill_click);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SkillTab->WidgetStyle.Hovered, UI_beforeBattle_skill_click);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SkillTab->WidgetStyle.Pressed, UI_beforeBattle_skill_click);
	}
	else {
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SkillTab->WidgetStyle.Normal, UI_beforeBattle_skill_default);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SkillTab->WidgetStyle.Hovered, UI_beforeBattle_skill_default);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SkillTab->WidgetStyle.Pressed, UI_beforeBattle_skill_default);
	}
}

void UPackageWidget::SpecialtyTabStyle(bool Clicked)
{
	if (Clicked) {
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SpecialtyTab->WidgetStyle.Normal, UI_beforeBattle_specialty_click);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SpecialtyTab->WidgetStyle.Hovered, UI_beforeBattle_specialty_click);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SpecialtyTab->WidgetStyle.Pressed, UI_beforeBattle_specialty_click);
	}
	else {
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SpecialtyTab->WidgetStyle.Normal, UI_beforeBattle_specialty_default);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SpecialtyTab->WidgetStyle.Hovered, UI_beforeBattle_specialty_default);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(SpecialtyTab->WidgetStyle.Pressed, UI_beforeBattle_specialty_default);
	}
}

void UPackageWidget::ItemTabStyle(bool Clicked)
{
	if (Clicked) {
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(ItemTab->WidgetStyle.Normal, UI_beforeBattle_item_click);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(ItemTab->WidgetStyle.Hovered, UI_beforeBattle_item_click);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(ItemTab->WidgetStyle.Pressed, UI_beforeBattle_item_click);
	}
	else {
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(ItemTab->WidgetStyle.Normal, UI_beforeBattle_item_default);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(ItemTab->WidgetStyle.Hovered, UI_beforeBattle_item_default);
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(ItemTab->WidgetStyle.Pressed, UI_beforeBattle_item_default);
	}
}

void UPackageWidget::Exit()
{
	RemoveFromParent();
	RemoveAllHoverWidgets();
}

void UPackageWidget::ResetSetting()
{
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		SelectedUIListArr[i]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
	}

	// 전체 선택 취소 시, 특수기는 취소하지 않는다.

	Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < SkillListArr.Num(); i++) {
		SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
	}
	for (int i = 0; i < SpecialtyListArr.Num(); i++) {
		SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
	}
	for (int i = 0; i < ItemListArr.Num(); i++) {
		ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
	}
}

void UPackageWidget::ClickSettingDone()
{
	// 스킬을 하나도 선택하지 않았다면 경고창을 띄운다.
	if (SelectedUIListArr[0]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
		SetIsEnabled(false);

		if (AlertModalClass) {
			AlertModalRef = CreateWidget<UAlertModalWidget>(GetWorld(), AlertModalClass);
			if (AlertModalRef) {
				AlertModalRef->AddToViewport();
			}
		}
		if (AlertModalRef) {
			AlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UPackageWidget::ClickAlertModalYes);
			AlertModalRef->Button_No->OnClicked.AddDynamic(this, &UPackageWidget::ClickAlertModalNo);
		}

		AlertModalRef->TextBlock_Skip->SetVisibility(ESlateVisibility::Visible);
		AlertModalRef->TextBlock_ItemName->SetVisibility(ESlateVisibility::Hidden);
		AlertModalRef->TextBlock_SelectOrNot->SetVisibility(ESlateVisibility::Hidden);
	}
	// 스킬을 하나라도 선택했다면 선택한 스킬, 특수기, 아이템 정보를 저장한다.
	else {
		SaveSelectedSkill();
		SaveSelectedSpecialty();
		SaveSelectedItem();

		RemoveFromParent();
		RemoveAllHoverWidgets();
	}
}

void UPackageWidget::ClickAlertModalYes()
{
	AlertModalRef->RemoveFromParent();
	SaveSelectedSkill();
	SaveSelectedSpecialty();
	if (Selected_Item->Image_Icon->GetVisibility() == ESlateVisibility::Visible) {
		SaveSelectedItem();
	}
	RemoveFromParent();
	RemoveAllHoverWidgets();
}

void UPackageWidget::ClickAlertModalNo()
{
	AlertModalRef->RemoveFromParent();
	SetIsEnabled(true);
}

void UPackageWidget::SaveSelectedSkill()
{
	BattleManagerSystem->SelectedSkillCodeList.Empty();
	// 선택한 스킬 저장
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		if (SelectedUIListArr[i]->Image_Icon->GetVisibility() == ESlateVisibility::Visible) {
			FString Iconname = SelectedUIListArr[i]->Image_Icon->Brush.GetResourceName().ToString();
			if (BattleManagerSystem->SkillIconRowMap.Find(Iconname)) {
				BattleManagerSystem->SelectedSkillCodeList.Add(BattleManagerSystem->SkillIconRowMap[Iconname]);
			}
			else {
				NTLOG(Warning, TEXT("Cannot Find SkillRow: %s!"), *Iconname);
			}
		}
		else
			break;
	}
}

void UPackageWidget::SaveSelectedSpecialty()
{
	FString IconName = Selected_Specialty->Image_Icon->Brush.GetResourceName().ToString();

	if (BattleManagerSystem->SpecialtyIconRowMap.Find(IconName)) {
		int RowNum = BattleManagerSystem->SpecialtyIconRowMap[IconName];
		BattleManagerSystem->FinalSpecialSkill = BattleTableManagerSystem->SpecialSkillTable->GetRowNames()[RowNum].ToString();
	}
	else {
		NTLOG(Warning, TEXT("Cannot Find SpecialtyRow: %s!"), *IconName);
	}
}

void UPackageWidget::SaveSelectedItem()
{
	// 선택한 아이템 저장
	if (Selected_Item->Image_Icon->GetVisibility() == ESlateVisibility::Visible) {
		FString IconName = Selected_Item->Image_Icon->Brush.GetResourceName().ToString();

		if (BattleManagerSystem->ItemIconRowMap.Find(IconName)) {
			int RowNum = BattleManagerSystem->ItemIconRowMap[IconName];
			BattleManagerSystem->FinalItem = BattleTableManagerSystem->ItemTable->GetRowNames()[RowNum].ToString();
		}
		else {
			NTLOG(Warning, TEXT("Cannot Find ItemRow: %s!"), *IconName);
		}
	}
}

void UPackageWidget::LoadBeforeSelectedSkills()
{
	for (int i = 0; i < BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
		SelectedUIListArr[i]->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[BattleManagerSystem->SelectedSkillCodeList[i]]->SkillIcon);
		SelectedUIListArr[i]->Image_Icon->SetVisibility(ESlateVisibility::Visible);
		SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
		SelectedSkillIconName.Add(SelectedUIListArr[i]->Image_Icon->Brush.GetResourceName().ToString());

		SkillListArr[BattleManagerSystem->SelectedSkillCodeList[i]]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	}

	if (BattleManagerSystem->FinalSpecialSkill != "") {
		Selected_Specialty->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->SpecialSkillTable->FindRow<FSpecialSkillTable>(FName(*BattleManagerSystem->FinalSpecialSkill), TEXT(""))->SpecialSkillIcon);
		Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Visible);


		FString IconName = Selected_Specialty->Image_Icon->Brush.GetResourceName().ToString();
		if (BattleManagerSystem->SpecialtyIconRowMap.Contains(IconName)) {
			SpecialtyListArr[BattleManagerSystem->SpecialtyIconRowMap[IconName]]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
		}
		else {
			NTLOG(Warning, TEXT("Cannot Find SpecialtyRow: %s!"), *IconName);
		}
	}
	else {
		Selected_Specialty->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->SpecialSkillTableRows[0]->SpecialSkillIcon);
		Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Visible);
		SpecialtyListArr[0]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	}

	if (BattleManagerSystem->FinalItem != "") {
		Selected_Item->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->ItemTable->FindRow<FItemData>(FName(*BattleManagerSystem->FinalItem), TEXT(""))->ItemIcon);
		Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Visible);
		Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Visible);

		FString IconName = Selected_Item->Image_Icon->Brush.GetResourceName().ToString();
		if (BattleManagerSystem->ItemIconRowMap.Contains(IconName)) {
			ItemListArr[*BattleManagerSystem->ItemIconRowMap.Find(IconName)]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
		}
		else {
			NTLOG(Warning, TEXT("Cannot Find ItemRow: %s!"), *IconName);
		}
	}
}

bool UPackageWidget::SelectSkill(FString IconName)
{
	// 스킬 선택칸이 다 찼다면 에러 애니메이션 실행 후 함수 종료
	if (SelectedUIListArr[SelectedUIListArr.Num() - 1]->Image_Icon->GetVisibility() == ESlateVisibility::Visible) {
		PlayAllSelectedSkillErrorAnim();
		return false;
	}
	
	int TableRowNum = BattleManagerSystem->FindSkillRow(IconName);
	SkillListArr[TableRowNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);

	for (int i = 0; i < 8; i++) {
		if (SelectedUIListArr[i]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
			SelectedUIListArr[i]->Image_Icon->SetVisibility(ESlateVisibility::Visible);
			SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
			SelectedUIListArr[i]->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[TableRowNum]->SkillIcon);
			SelectedSkillIconName.Add(IconName);
			break;
		}
	}
	return true;
}

void UPackageWidget::CancelSkill(FString IconName)
{
	int SkillListRowNum = BattleManagerSystem->FindSkillRow(IconName);
	SkillListArr[SkillListRowNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
	SelectedSkillIconName.Remove(IconName);
	UpdateSelectedSkillIcon();
}

void UPackageWidget::UpdateSelectedSkillIcon()
{
	for (int i = 0; i < SelectedSkillIconName.Num(); i++) {
		int RowNum = BattleManagerSystem->FindSkillRow(SelectedSkillIconName[i]);
		SelectedUIListArr[i]->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIcon);
	}
	SelectedUIListArr[SelectedSkillIconName.Num()]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	SelectedUIListArr[SelectedSkillIconName.Num()]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
}

void UPackageWidget::SelectSpecialSkill(FString IconName)
{
	int TableRowNum = BattleManagerSystem->FindSpecialtyRow(IconName);

	for (int i = 0; i < SpecialtyListArr.Num(); i++) {
		if (SpecialtyListArr[i]->Image_CheckBox->Brush.GetResourceObject() == icon_checkbox_selected) {
			SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
			break;
		}
	}

	SpecialtyListArr[TableRowNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	Selected_Specialty->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->SpecialSkillTableRows[TableRowNum]->SpecialSkillIcon);
}

void UPackageWidget::SelectItem(FString IconName)
{
	int TableRowNum = BattleManagerSystem->FindItemRow(IconName);
	
	if (KNOCKturneGameState->ItemCountList[TableRowNum] == 0)
		return;

	for (int i = 0; i < ItemListArr.Num(); i++) {
		if (ItemListArr[i]->Image_CheckBox->Brush.GetResourceObject() == icon_checkbox_selected) {
			ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
			break;
		}
	}

	ItemListArr[TableRowNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	Selected_Item->Image_Icon->SetBrushFromTexture(BattleTableManagerSystem->ItemTableRows[TableRowNum]->ItemIcon);
	Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Visible);
	Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
}

void UPackageWidget::CancelItem(FString IconName)
{
	int ItemListRowNum = BattleManagerSystem->FindItemRow(IconName);
	ItemListArr[ItemListRowNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);

	Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
}

void UPackageWidget::PlayAllSelectedSkillErrorAnim()
{
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		SelectedUIListArr[i]->PlaySkillErrorAnim();
	}
}

void UPackageWidget::RemoveAllHoverWidgets()
{
	TArray<UUserWidget*> SkillHoverWidgetArr;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, SkillHoverWidgetArr, PackageSkillHoverWidgetClass);
	if (SkillHoverWidgetArr.Num() > 0) {
		for (auto HoverWidget : SkillHoverWidgetArr)
			HoverWidget->RemoveFromParent();
	}

	TArray<UUserWidget*> SpecialSkillHoverWidgetArr;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, SpecialSkillHoverWidgetArr, SpecialSkillHoverWidgetClass);
	if (SpecialSkillHoverWidgetArr.Num() > 0) {
		for (auto HoverWidget : SpecialSkillHoverWidgetArr)
			HoverWidget->RemoveFromParent();
	}

	TArray<UUserWidget*> ItemHoverWidgetArr;;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, ItemHoverWidgetArr, ItemSkillHoverWidgetClass);
	if (ItemHoverWidgetArr.Num() > 0) {
		for (auto HoverWidget : ItemHoverWidgetArr)
			HoverWidget->RemoveFromParent();
	}
}
