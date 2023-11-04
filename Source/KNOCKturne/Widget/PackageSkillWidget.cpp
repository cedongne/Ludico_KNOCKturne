// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include "Pac_SelectedUI_Widget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "SpecialtyListFormWidget.h"
#include "ItemListFormWidget.h"

UPackageSkillWidget::UPackageSkillWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	FString PeppySkillTablePath = TEXT("/Game/Assets/DataTable/PeppySkillTable.PeppySkillTable");
	FString SpecialSkillTablePath = TEXT("/Game/Assets/DataTable/SpecialSkillTable.SpecialSkillTable");
	FString ItemTablePath = TEXT("/Game/Assets/DataTable/ItemTable.ItemTable");
	FString SkillBuffStringTablePath = TEXT("/Game/Assets/DataTable/SkillBuffStringTable.SkillBuffStringTable");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSKILLTABLE(*PeppySkillTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SPECIALSKILLTABLE(*SpecialSkillTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*ItemTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLBUFFSTRINGTABLE(*SkillBuffStringTablePath);
	PeppySkillTable = DT_PEPPYSKILLTABLE.Object;
	SpecialSkillTable = DT_SPECIALSKILLTABLE.Object;
	ItemTable = DT_ITEMTABLE.Object;
	SkillBuffStringTable = DT_SKILLBUFFSTRINGTABLE.Object;
}

void UPackageSkillWidget::NativePreConstruct() {
	Super::NativePreConstruct();

}

void UPackageSkillWidget::NativeConstruct() {
	Super::NativeConstruct();

	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	PeppySkillTable->GetAllRows<FPeppySkillData>("GetAllRows", PeppySkillTableRows);
	SpecialSkillTable->GetAllRows<FSpecialSkillData>("GetAllRows", SpecialSkillTableRows);
	ItemTable->GetAllRows<FItemData>("GetAllRows", ItemTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);

	CreateSkillList();
	CreateSelectedSkillList();
	CreateSpecialtyList();
	CreateItemList();

	if (SkillTab) {
		SkillTab->OnClicked.AddDynamic(this, &UPackageSkillWidget::OnClick_SkillTab);
	}
	if (SpecialtyTab) {
		SpecialtyTab->OnClicked.AddDynamic(this, &UPackageSkillWidget::OnClick_SpecialtyTab);
	}
	if (ItemTab) {
		ItemTab->OnClicked.AddDynamic(this, &UPackageSkillWidget::OnClick_ItemTab);
	}
	if (Button_Exit) {
		Button_Exit->OnClicked.AddDynamic(this, &UPackageSkillWidget::OnClick_Exit);
	}
	if (Button_Reset) {
		Button_Reset->OnClicked.AddDynamic(this, &UPackageSkillWidget::OnClick_Reset);
	}

}

void UPackageSkillWidget::CreateSkillList() {
	int row = 0;

	for (int i = 0; i < 14; i++) {
		if (SkillListFormClass) {
			SkillListFormRef = CreateWidget<USkillListFormWidget>(GetWorld(), SkillListFormClass);
			if (SkillListFormRef) {
				SkillListArr.Add(SkillListFormRef);
				if (i % 2 == 1) {
					UniformGridPanel_Skill->AddChildToUniformGrid(SkillListFormRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_Skill->AddChildToUniformGrid(SkillListFormRef, row, 0);
				}

				SetSkillUI(SkillListFormRef, i);
			}
		}
	}
}

void UPackageSkillWidget::CreateSelectedSkillList() {
	int row = 0;

	for (int i = 0; i < 8; i++) {
		if (SelectedUIClass) {
			SelectedUIRef = CreateWidget<UPac_SelectedUI_Widget>(GetWorld(), SelectedUIClass);
			if (SelectedUIRef) {
				SelectedUIListArr.Add(SelectedUIRef);
				if (i % 2 == 1) {
					UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, row, 0);
				}
			}
		}
	}
}

void UPackageSkillWidget::SetSkillUI(USkillListFormWidget* SkillListForm, int idx) {
	UTexture2D* iconimg = PeppySkillTableRows[idx]->SkillIcon;
	SkillListForm->Image_Icon->SetBrushFromTexture(iconimg);

	FString stringid = *(PeppySkillTableRows[idx]->SkillId);
	FString name = SkillBuffStringTable->FindRow<FDialogueString>(FName(*stringid.Append("_String")), TEXT(""))->KOR;
	SkillListForm->TextBlock_SkillName->SetText(FText::FromString(name));

	FString stance = SkillBuffStringTable->FindRow<FDialogueString>(FName(*(PeppySkillTableRows[idx]->SkillStance)), TEXT(""))->KOR;
	SkillListForm->TextBlock_Stance->SetText(FText::FromString(stance));

	FString cooltime = FString::FromInt(PeppySkillTableRows[idx]->SkillCoolTurn);
	SkillListForm->TextBlock_CoolTimeSec->SetText(FText::FromString(cooltime));

	FString energy = FString::FromInt(PeppySkillTableRows[idx]->Cost);
	SkillListForm->TextBlock_Energy->SetText(FText::FromString(energy));
}

void UPackageSkillWidget::CreateSpecialtyList() {
	int row = 0;

	for (int i = 0; i < 8; i++) {
		if (i == 5 || i == 7) {
			if (BP_BlankSpaceClass) {
				BP_BlankSpaceRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlankSpaceClass);
				if (BP_BlankSpaceRef) {
					UniformGridPanel_Specialty->AddChildToUniformGrid(BP_BlankSpaceRef, row, 1);
					++row;
				}
			}
		}
		else {
			if (SpecialtyListFormClass) {
				SpecialtyListFormRef = CreateWidget<USpecialtyListFormWidget>(GetWorld(), SpecialtyListFormClass);
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

void UPackageSkillWidget::SetSpecialtyUI(USpecialtyListFormWidget* SpecialtyListForm, int idx)
{
	UTexture2D* iconimg = SpecialSkillTableRows[idx]->SpecialSkillIcon;
	SpecialtyListForm->Image_Icon->SetBrushFromTexture(iconimg);

	FString stringid = SpecialSkillTable->GetRowNames()[idx].ToString();
	FString name = SkillBuffStringTable->FindRow<FDialogueString>(FName(*stringid.Append("_String")), TEXT(""))->KOR;
	SpecialtyListForm->TextBlock_SkillName->SetText(FText::FromString(name));

	FString cooltime = FString::FromInt(SpecialSkillTableRows[idx]->CoolTime);
	SpecialtyListForm->TextBlock_CoolTimeSec->SetText(FText::FromString(cooltime));

	FString energy = FString::FromInt(SpecialSkillTableRows[idx]->EnergyCost);
	SpecialtyListForm->TextBlock_Energy->SetText(FText::FromString(energy));
}

void UPackageSkillWidget::CreateItemList() {
	int row = 0;

	for (int i = 0; i < 8; i++) {
		if (i == 5 || i == 7) {
			if (BP_BlankSpaceClass) {
				BP_BlankSpaceRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlankSpaceClass);
				if (BP_BlankSpaceRef) {
					UniformGridPanel_Item->AddChildToUniformGrid(BP_BlankSpaceRef, row, 1);
					++row;
				}
			}
		}
		else {
			if (ItemListFormClass) {
				ItemListFormRef = CreateWidget<UItemListFormWidget>(GetWorld(), ItemListFormClass);
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

void UPackageSkillWidget::SetItemUI(UItemListFormWidget* ItemListForm, int idx)
{
	UTexture2D* iconimg = ItemTableRows[idx]->ItemIcon;
	ItemListForm->Image_Icon->SetBrushFromTexture(iconimg);

	FString stringid = ItemTable->GetRowNames()[idx].ToString();
	FString name = SkillBuffStringTable->FindRow<FDialogueString>(FName(*stringid.Append("_String")), TEXT(""))->KOR;
	ItemListForm->TextBlock_SkillName->SetText(FText::FromString(name));

	FString count = FString::FromInt(KNOCKturneGameState->ItemCountList[idx]);
	ItemListForm->TextBlock_Count->SetText(FText::FromString(count));
}

void UPackageSkillWidget::OnClick_SkillTab() {
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

void UPackageSkillWidget::OnClick_SpecialtyTab() {
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

void UPackageSkillWidget::OnClick_ItemTab() {
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

void UPackageSkillWidget::SkillTabStyle(bool Clicked) {
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

void UPackageSkillWidget::SpecialtyTabStyle(bool Clicked) {
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

void UPackageSkillWidget::ItemTabStyle(bool Clicked) {
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

void UPackageSkillWidget::OnClick_Exit()
{
	RemoveFromParent();
}

void UPackageSkillWidget::OnClick_Reset()
{
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		SelectedUIListArr[i]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
	}

	Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	Selected_Specialty->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
	Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
}
