// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PeppyTurnUIWidget.h"
#include "PeppyTurnSkillCardWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"
#include "GameInstance/ActorManagerSystem.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "PeppyTurnSelectedIconWidget.h"
#include "Widget/AlertModalWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UPeppyTurnUIWidget::NativePreConstruct()
{
	UniformGridPanel_Skill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Skill"));
	UniformGridPanel_SelectedSkill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_SelectedSkill"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_EnergyWarning = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyWarning"));
	Button_Attack = (UButton*)GetWidgetFromName(TEXT("Button_Attack"));
	Button_Skip = (UButton*)GetWidgetFromName(TEXT("Button_Skip"));
	Button_Reset = (UButton*)GetWidgetFromName(TEXT("Button_Reset"));
}

void UPeppyTurnUIWidget::NativeConstruct()
{
	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = GameInstance->GetSubsystem<UActorManagerSystem>();

	CreateSkillList();
	CreateSelectedSkillList();
	PlayPeppyTurnAppearAnim();

	Button_Reset->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ResetSetting);
	Button_Attack->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ClickAttack);
	Button_Skip->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ClickSkip);
}

void UPeppyTurnUIWidget::CreateSkillList()
{
	BattleManagerSystem->SelectedSkillCodeList.Add(0);
	BattleManagerSystem->SelectedSkillCodeList.Add(1);
	BattleManagerSystem->SelectedSkillCodeList.Add(2);
	BattleManagerSystem->SelectedSkillCodeList.Add(3);
	BattleManagerSystem->SelectedSkillCodeList.Add(5);
	BattleManagerSystem->SelectedSkillCodeList.Add(6);
	BattleManagerSystem->SelectedSkillCodeList.Add(11);
	BattleManagerSystem->SelectedSkillCodeList.Add(12);

	int row = 0;
	
	for (int i = 0; i < BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
		if (PeppyTurnSkillCardWidgetClass) {
			UPeppyTurnSkillCardWidget* SkillListFormRef = CreateWidget<UPeppyTurnSkillCardWidget>(GetWorld(), PeppyTurnSkillCardWidgetClass);
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
				IconNameRowMap.Add(SkillListFormRef->Image_Icon->Brush.GetResourceName().ToString(), i);
			}
		}
	}

	int WidgetSequence = BattleManagerSystem->SelectedSkillCodeList.Num();
	for (int i = 0; i < 8 - BattleManagerSystem->SelectedSkillCodeList.Num(); i++) {
		if (BP_BlankSpaceClass) {
			UUserWidget* BP_BlankSpaceRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlankSpaceClass);
			if (BP_BlankSpaceRef) {
				if (WidgetSequence % 2 == 1) {
					UniformGridPanel_Skill->AddChildToUniformGrid(BP_BlankSpaceRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_Skill->AddChildToUniformGrid(BP_BlankSpaceRef, row, 0);
				}
				WidgetSequence++;
			}
		}
	}
}

void UPeppyTurnUIWidget::SetSkillUI(UPeppyTurnSkillCardWidget* PeppyTurnSkillCardWidget, int RowNum)
{
	UTexture2D* Icon = BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIcon;
	PeppyTurnSkillCardWidget->Image_Icon->SetBrushFromTexture(Icon);

	FString SkillId = *(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillId);
	FString Name = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SkillId.Append("_String")), TEXT(""))->KOR;
	PeppyTurnSkillCardWidget->TextBlock_SkillName->SetText(FText::FromString(Name));

	FString Stance = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillStance)), TEXT(""))->KOR;
	PeppyTurnSkillCardWidget->TextBlock_Stance->SetText(FText::FromString(Stance));

	FString CoolTime = FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillCoolTurn);
	PeppyTurnSkillCardWidget->TextBlock_CoolTimeSec->SetText(FText::FromString(CoolTime));

	FString Energy = FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Cost);
	PeppyTurnSkillCardWidget->TextBlock_Energy->SetText(FText::FromString(Energy));
}

void UPeppyTurnUIWidget::CreateSelectedSkillList()
{
	for (int i = 0; i < 4; i++) {
		if (SelectedUIClass) {
			UPeppyTurnSelectedUIWidget* SelectedUIRef = CreateWidget<UPeppyTurnSelectedUIWidget>(GetWorld(), SelectedUIClass);
			if (SelectedUIRef) {
				SelectedUIListArr.Add(SelectedUIRef);
				UniformGridPanel_SelectedSkill->AddChildToUniformGrid(SelectedUIRef, 0, i);
				SelectedUIRef->TextBlock_SelectNum->SetText(FText::FromString(FString::FromInt(i + 1)));
			}
		}
	}
}

void UPeppyTurnUIWidget::ResetSetting()
{
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		SelectedUIListArr[i]->BP_PeppyTurnIcon->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->Image_NumBackground->SetVisibility(ESlateVisibility::Hidden);
		SelectedUIListArr[i]->TextBlock_SelectNum->SetVisibility(ESlateVisibility::Hidden);
	}

	for (int i = 0; i < SkillListArr.Num(); i++) {
		SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
		SkillListArr[i]->TextBlock_Num->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPeppyTurnUIWidget::ClickAlertModalYes()
{
	BattleManagerSystem->isSkipPeppyTurn = true;
	AlertModalRef->RemoveFromParent();
	RemoveAllHoverWidgets();
	RemoveFromParent();
	BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));
	BattleManager->EndTurn();
}

void UPeppyTurnUIWidget::ClickAlertModalNo()
{
	AlertModalRef->RemoveFromParent();
	SetIsEnabled(true);
}

void UPeppyTurnUIWidget::AddEnergy(int EnergyCost)
{
	TotalSelectedEnergyCost += EnergyCost;
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(TotalSelectedEnergyCost)));
	SetEnergyWarningText();
}

void UPeppyTurnUIWidget::MinusEnergy(int EnergyCost)
{
	TotalSelectedEnergyCost -= EnergyCost;
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(TotalSelectedEnergyCost)));
	SetEnergyWarningText();
}

void UPeppyTurnUIWidget::SetEnergyWarningText()
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

void UPeppyTurnUIWidget::ClickSkip()
{
	SetIsEnabled(false);

	if (AlertModalClass) {
		AlertModalRef = CreateWidget<UAlertModalWidget>(GetWorld(), AlertModalClass);
		if (AlertModalRef) {
			AlertModalRef->AddToViewport();
			AlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ClickAlertModalYes);
			AlertModalRef->Button_No->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ClickAlertModalNo);
		}
	}

	AlertModalRef->TextBlock_Skip->SetVisibility(ESlateVisibility::Visible);
	AlertModalRef->TextBlock_ItemName->SetVisibility(ESlateVisibility::Hidden);
	AlertModalRef->TextBlock_SelectOrNot->SetVisibility(ESlateVisibility::Hidden);
}

void UPeppyTurnUIWidget::SetSkillActorList()
{
	BattleManagerSystem->SelectedSkillActorClassList.Empty();

	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		if (SelectedUIListArr[i]->Button_Cancel->GetVisibility() == ESlateVisibility::Visible) {
			FString iconname = SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString();
			if (BattleManagerSystem->IconSkillActorMap.Contains(iconname)) {
				if (UKismetSystemLibrary::IsValidClass(*(BattleManagerSystem->IconSkillActorMap[iconname]))) {
					BattleManagerSystem->SelectedSkillActorClassList.Add(*BattleManagerSystem->IconSkillActorMap[iconname]);
					BattleManagerSystem->SelectedSkillIconNameList.Add(iconname);
				}
			}
		}
		else
			BattleManagerSystem->SelectedSkillIconNameList.Add("None");
	}

	RemoveAllHoverWidgets();
	RemoveFromParent();
	BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));
	BattleManager->EndTurn();
}

void UPeppyTurnUIWidget::ClickAttack()
{
	BattleManagerSystem->isSkipPeppyTurn = false;

	if (SkillListArr.Num() == 0) {
		RemoveAllHoverWidgets();
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
					AlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ClickAlertModalYes);
					AlertModalRef->Button_No->OnClicked.AddDynamic(this, &UPeppyTurnUIWidget::ClickAlertModalNo);
				}
			}

			AlertModalRef->TextBlock_Skip->SetVisibility(ESlateVisibility::Visible);
			AlertModalRef->TextBlock_ItemName->SetVisibility(ESlateVisibility::Hidden);
			AlertModalRef->TextBlock_SelectOrNot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPeppyTurnUIWidget::RemoveAllHoverWidgets()
{
	TArray<UUserWidget*> SkillHoverWidgetArr;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, SkillHoverWidgetArr, PeppyTurnSkillHoverWidgetClass);
	if (SkillHoverWidgetArr.Num() > 0) {
		for (auto HoverWidget : SkillHoverWidgetArr)
			HoverWidget->RemoveFromParent();
	}
}

bool UPeppyTurnUIWidget::SelectSkill(FString IconName)
{
	bool isSelectSkill = false;
	int TableRowNum = BattleManagerSystem->FindSkillRow(IconName);
	int CurSequenceNum = 0;

	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		if (SelectedUIListArr[i]->BP_PeppyTurnIcon->GetVisibility() == ESlateVisibility::Hidden) {
			SelectedUIListArr[i]->BP_PeppyTurnIcon->SetVisibility(ESlateVisibility::Visible);
			SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
			SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[TableRowNum]->SkillIcon);
			SelectedUIListArr[i]->Image_NumBackground->SetVisibility(ESlateVisibility::Visible);
			SelectedUIListArr[i]->TextBlock_SelectNum->SetVisibility(ESlateVisibility::Visible);
			SelectedUIListArr[i]->TextBlock_SelectNum->SetText(FText::FromString(FString::FromInt(i + 1)));
			IconSequenceRowMap.Add(SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString(), i + 1);
			CurSequenceNum = i + 1;
			isSelectSkill = true;
			break;
		}
	}

	// 스킬 선택칸이 다 찼다면 에러 애니메이션 실행 후 함수 종료
	if (!isSelectSkill) {
		PlayAllSelectedSkillErrorAnim();
		return false;
	}

	int SkillListNum = *IconNameRowMap.Find(IconName);
	SkillListArr[SkillListNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_numbering);
	SkillListArr[SkillListNum]->TextBlock_Num->SetVisibility(ESlateVisibility::Visible);
	SkillListArr[SkillListNum]->TextBlock_Num->SetText(FText::FromString(FString::FromInt(CurSequenceNum)));

	AddEnergy(BattleTableManagerSystem->PeppySkillTableRows[TableRowNum]->Cost);
	return true;
}

void UPeppyTurnUIWidget::CancelSkill(FString IconName)
{
	int SkillListNum = *IconNameRowMap.Find(IconName);
	SkillListArr[SkillListNum]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
	SkillListArr[SkillListNum]->TextBlock_Num->SetVisibility(ESlateVisibility::Hidden);

	int SelectedUINum = IconSequenceRowMap[IconName] - 1;
	SelectedUIListArr[SelectedUINum]->BP_PeppyTurnIcon->SetVisibility(ESlateVisibility::Hidden);
	SelectedUIListArr[SelectedUINum]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
	SelectedUIListArr[SelectedUINum]->Image_NumBackground->SetVisibility(ESlateVisibility::Hidden);
	SelectedUIListArr[SelectedUINum]->TextBlock_SelectNum->SetVisibility(ESlateVisibility::Hidden);

	int TableRowNum = BattleManagerSystem->FindSkillRow(IconName);
	MinusEnergy(BattleTableManagerSystem->PeppySkillTableRows[TableRowNum]->Cost);

	IconSequenceRowMap.Remove(IconName);
}

void UPeppyTurnUIWidget::PlayAllSelectedSkillErrorAnim()
{
	for (int i = 0; i < SelectedUIListArr.Num(); i++) {
		SelectedUIListArr[i]->PlaySkillErrorAnim();
	}
}
