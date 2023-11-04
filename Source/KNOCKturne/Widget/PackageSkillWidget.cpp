// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include "Pac_SelectedUI_Widget.h"

UPackageSkillWidget::UPackageSkillWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	FString PeppySkillTablePath = TEXT("/Game/Assets/DataTable/PeppySkillTable.PeppySkillTable");
	FString SkillBuffStringTablePath = TEXT("/Game/Assets/DataTable/SkillBuffStringTable.SkillBuffStringTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*PeppySkillTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLBUFFSTRINGTABLE(*SkillBuffStringTablePath);
	PeppySkillTable = DT_ITEMTABLE.Object;
	SkillBuffStringTable = DT_SKILLBUFFSTRINGTABLE.Object;
}

void UPackageSkillWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	UniformGridPanel_Skill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Skill"));
}

void UPackageSkillWidget::NativeConstruct() {
	Super::NativeConstruct();

	PeppySkillTable->GetAllRows<FPeppySkillData>("GetAllRows", PeppySkillTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);

	CreateSkillList();
	CreateSelectedSkillList();
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