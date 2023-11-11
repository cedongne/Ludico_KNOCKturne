// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PeppyTurnWidget.h"
#include <Kismet/GameplayStatics.h>
#include "SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurn_SelectedUI_Widget.h"

UPeppyTurnWidget::UPeppyTurnWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	FString PeppySkillTablePath = TEXT("/Game/Assets/DataTable/PeppySkillTable.PeppySkillTable");
	FString SkillBuffStringTablePath = TEXT("/Game/Assets/DataTable/SkillBuffStringTable.SkillBuffStringTable");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSKILLTABLE(*PeppySkillTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLBUFFSTRINGTABLE(*SkillBuffStringTablePath);

	PeppySkillTable = DT_PEPPYSKILLTABLE.Object;
	SkillBuffStringTable = DT_SKILLBUFFSTRINGTABLE.Object;
}

void UPeppyTurnWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	PeppySkillTable->GetAllRows<FPeppySkillData>("GetAllRows", PeppySkillTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);

	// ---테스트용
	BattleManagerSystem->SetSizeOfSelectedSkillCodeList(8);
	BattleManagerSystem->SetOneSelectedSkillCodeList(0, 1);
	BattleManagerSystem->SetOneSelectedSkillCodeList(1, 4);
	BattleManagerSystem->SetOneSelectedSkillCodeList(2, 5);
	BattleManagerSystem->SetOneSelectedSkillCodeList(3, 7);
	BattleManagerSystem->SetOneSelectedSkillCodeList(4, 3);
	BattleManagerSystem->SetOneSelectedSkillCodeList(5, 2);
	BattleManagerSystem->SetOneSelectedSkillCodeList(6, 10);
	BattleManagerSystem->SetOneSelectedSkillCodeList(7, 12);
	// ---
}

void UPeppyTurnWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (SkillListFormRef->SkillHoverWidgetRef) {
		RemoveSelectedHoverWidget();
	}
}

void UPeppyTurnWidget::CreateSkillList() {
	int row = 0;

	for (int i = 0; i < BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
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

				SetSkillUI(SkillListFormRef, BattleManagerSystem->SelectedSkillCodeList[i]);
			}
		}
	}

	for (int i = BattleManagerSystem->SelectedSkillCodeList.Num(); i < 8 - BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
		if (BP_BlankSpaceClass) {
			BP_BlankSpaceRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlankSpaceClass);
			if (BP_BlankSpaceRef) {
				if (i % 2 == 1) {
					UniformGridPanel_Skill->AddChildToUniformGrid(BP_BlankSpaceRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_Skill->AddChildToUniformGrid(BP_BlankSpaceRef, row, 0);
				}
			}
		}
	}
}

void UPeppyTurnWidget::SetSkillUI(USkillListFormWidget* SkillListForm, int idx) {
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

void UPeppyTurnWidget::CreateSelectedSkillList()
{
	int row = 0;

	for (int i = 0; i < 4; i++) {
		if (SelectedUIClass) {
			SelectedUIRef = CreateWidget<UPeppyTurn_SelectedUI_Widget>(GetWorld(), SelectedUIClass);
			if (SelectedUIRef) {
				SelectedUIListArr.Add(SelectedUIRef);
				if (i % 2 == 1) {
					UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, row, 0);
				}
				SelectedUIRef->TextBlock_SelectNum->SetText(FText::FromString(FString::FromInt(i + 1)));
			}
		}
	}
}

void UPeppyTurnWidget::RemoveSelectedHoverWidget()
{
	/*if (SkillListFormRef->SkillHoverWidgetRef) {
		for (int i = 0; i < SelectedUIListArr.Num(); i++) {
			if (SelectedUIListArr[i]->Image_Icon->Brush.GetResourceName() == SkillListFormRef->SkillHoverWidgetRef->Image_Icon->Brush.GetResourceName()) {
				SelectedUIBtn = SelectedUIListArr[i]->Button_Background;
				break;
			}
		}

		if (SkillListFormRef->SkillHoverWidgetRef->IsHovered() == false && SelectedUIBtn->IsHovered() == false) {
			SkillListFormRef->SkillHoverWidgetRef->RemoveFromParent();
		}
	}*/
}
