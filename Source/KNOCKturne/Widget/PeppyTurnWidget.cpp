// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PeppyTurnWidget.h"
#include <Kismet/GameplayStatics.h>
#include "SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurn_SelectedUI_Widget.h"
#include "GameInstance/ActorManagerSystem.h"
#include "Kismet/KismetMathLibrary.h"

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
	ActorManagerSystem = GameInstance->GetSubsystem<UActorManagerSystem>();

	PeppySkillTable->GetAllRows<FPeppySkillData>("GetAllRows", PeppySkillTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);

	CreateSkillList();
	CreateSelectedSkillList();

	Button_Reset->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_Reset);
	Button_Attack->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_Attack);
	Button_Skip->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_Skip);
}

void UPeppyTurnWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

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

	for (int i = 0; i < 8 - BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
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
	for (int i = 0; i < 4; i++) {
		if (SelectedUIClass) {
			SelectedUIRef = CreateWidget<UPeppyTurn_SelectedUI_Widget>(GetWorld(), SelectedUIClass);
			if (SelectedUIRef) {
				SelectedUIListArr.Add(SelectedUIRef);
				UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, 0, i);
				SelectedUIRef->TextBlock_SelectNum->SetText(FText::FromString(FString::FromInt(i + 1)));
			}
		}
	}
}

void UPeppyTurnWidget::OnClick_Reset()
{
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		SelectedUIListArr[i]->BP_PeppyTurnIcon->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->Image_NumBackground->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->TextBlock_SelectNum->SetVisibility(ESlateVisibility::Hidden);
	}

	for (int i = 0; i < SkillListArr.Num(); i++) {
		SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(SkillListFormRef->icon_checkbox);
	}
}

void UPeppyTurnWidget::OnClick_AlertModalYes() {
	AlertModalRef->RemoveFromParent();
	RemoveFromParent();
	SetSkillActorList();
}

void UPeppyTurnWidget::OnClick_AlertModalNo() {
	AlertModalRef->RemoveFromParent();
	SetIsEnabled(true);
}

void UPeppyTurnWidget::AddEnergy(int EnergyCost)
{
	TotalSelectedEnergyCost += EnergyCost;
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(TotalSelectedEnergyCost)));
	SetEnergyWarningText();	
}

void UPeppyTurnWidget::MinusEnergy(int EnergyCost)
{
	TotalSelectedEnergyCost -= EnergyCost;
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(TotalSelectedEnergyCost)));
	SetEnergyWarningText();
}

void UPeppyTurnWidget::SetEnergyWarningText()
{
	if (TotalSelectedEnergyCost - (ActorManagerSystem->PeppyActor->StatComponent->CurStatData.Energy) > 0) {
		TextBlock_Energy->SetColorAndOpacity(FLinearColor(1.f, 0.074214f, 0.074214f, 1.f));
		int ExceededEnergyCost = TotalSelectedEnergyCost - (ActorManagerSystem->PeppyActor->StatComponent->CurStatData.Energy);
		FString warningTxt = FString::Printf(TEXT("이용 가능한 에너지를 %d 초과했습니다."), ExceededEnergyCost);
		TextBlock_EnergyWarning->SetText(FText::FromString(warningTxt));
		TextBlock_EnergyWarning->SetVisibility(ESlateVisibility::Visible);
		Button_Attack->SetIsEnabled(false);
	}
	else {
		TextBlock_Energy->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		TextBlock_EnergyWarning->SetVisibility(ESlateVisibility::Hidden);
		Button_Attack->SetIsEnabled(true);
	}
}

void UPeppyTurnWidget::OnClick_Skip()
{
	SetIsEnabled(false);

	if (AlertModalClass) {
		AlertModalRef = CreateWidget<UAlertModalWidget>(GetWorld(), AlertModalClass);
		if (AlertModalRef) {
			AlertModalRef->AddToViewport();
			AlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_AlertModalYes);
			AlertModalRef->Button_No->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_AlertModalNo);
		}
	}

	AlertModalRef->TextBlock_Skip->SetVisibility(ESlateVisibility::Visible);
	AlertModalRef->TextBlock_ItemName->SetVisibility(ESlateVisibility::Hidden);
	AlertModalRef->TextBlock_SelectOrNot->SetVisibility(ESlateVisibility::Hidden);
}

void UPeppyTurnWidget::SetSkillActorList()
{
	BattleManagerSystem->SelectedSkillActorClassList.Empty();

	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		if (SelectedUIListArr[i]->Button_Cancel->GetVisibility() == ESlateVisibility::Visible) {
			FString iconname = SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString();
			if (BattleManagerSystem->IconSkillActorMap.Contains(iconname)) {
				if (UKismetSystemLibrary::IsValidClass(*(BattleManagerSystem->IconSkillActorMap[iconname]))) {
					BattleManagerSystem->SelectedSkillActorClassList.Add(*BattleManagerSystem->IconSkillActorMap[iconname]);
				}
			}
		}
	}

	RemoveFromParent();
	BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));
	BattleManager->EndTurn();
}

void UPeppyTurnWidget::OnClick_Attack()
{
	if (SkillListArr.Num() == 0) {
		RemoveFromParent();
	}
	else {
		bool SelectedSkillExist = false;

		for (int i = 0; i < SelectedUIListArr.Num(); i++) {
			if (SelectedUIListArr[i]->Button_Cancel->GetVisibility() == ESlateVisibility::Visible) {
				SelectedSkillExist = true;
				break;
			}
		}

		if (SelectedSkillExist) {
			SetSkillActorList();
		}
		else {
			SetIsEnabled(false);

			if (AlertModalClass) {
				AlertModalRef = CreateWidget<UAlertModalWidget>(GetWorld(), AlertModalClass);
				if (AlertModalRef) {
					AlertModalRef->AddToViewport();
					AlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_AlertModalYes);
					AlertModalRef->Button_No->OnClicked.AddDynamic(this, &UPeppyTurnWidget::OnClick_AlertModalNo);
				}
			}

			AlertModalRef->TextBlock_Skip->SetVisibility(ESlateVisibility::Visible);
			AlertModalRef->TextBlock_ItemName->SetVisibility(ESlateVisibility::Hidden);
			AlertModalRef->TextBlock_SelectOrNot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
