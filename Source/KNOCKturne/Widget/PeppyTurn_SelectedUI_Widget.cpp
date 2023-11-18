// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PeppyTurn_SelectedUI_Widget.h"
#include "SkillHoverWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurnWidget.h"
#include "SkillListFormWidget.h"

void UPeppyTurn_SelectedUI_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPeppyTurn_SelectedUI_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
	PeppyTurnWidget = (UPeppyTurnWidget*)PeppyTurnWidgetArr[0];

	Button_Cancel->OnClicked.AddDynamic(this, &UPeppyTurn_SelectedUI_Widget::OnClick_CancelSkill);
	//Button_Background->OnHovered.AddDynamic(this, &UPeppyTurn_SelectedUI_Widget::OnHovered_SelectedSkill);
}

void UPeppyTurn_SelectedUI_Widget::NativeTick(const FGeometry& Geometry, float DeltaSeconds) {
	Super::NativeTick(Geometry, DeltaSeconds);

	if (PeppyTurnWidget->SkillListFormRef->SkillHoverWidgetRef) {
		PeppyTurnWidget->SkillListFormRef->SkillDescriptionComponent->RemoveSelectedHoverWidget();
	}

	if (BP_PeppyTurnIcon->Image_SelectedSkillIcon->IsHovered()) {
		OnHovered_SelectedSkill();
	}
}

void UPeppyTurn_SelectedUI_Widget::CancelSkill(int tablecancelNum, USkillHoverWidget* SkillHover)
{
	int cancelNuminSelectedUI = 0;
	cancelimg = PeppyTurnWidget->PeppySkillTableRows[tablecancelNum]->SkillIcon;

	for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush) == cancelimg) {
			cancelNuminSelectedUI = i;
			break;
		}
	}

	for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush) == cancelimg) {
			PeppyTurnWidget->SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(PeppyTurnWidget->SkillListFormRef->icon_checkbox);
			PeppyTurnWidget->SkillListArr[i]->TextBlock_Num->SetVisibility(ESlateVisibility::Hidden);
			SkillHover->Image_CheckBox->SetBrushFromTexture(PeppyTurnWidget->SkillListFormRef->icon_checkbox);
			SkillHover->TextBlock_Num->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	PeppyTurnWidget->SelectedUIListArr[cancelNuminSelectedUI]->BP_PeppyTurnIcon->SetVisibility(ESlateVisibility::Hidden);
	PeppyTurnWidget->SelectedUIListArr[cancelNuminSelectedUI]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
	PeppyTurnWidget->SelectedUIListArr[cancelNuminSelectedUI]->Image_NumBackground->SetVisibility(ESlateVisibility::Hidden);
	PeppyTurnWidget->SelectedUIListArr[cancelNuminSelectedUI]->TextBlock_SelectNum->SetVisibility(ESlateVisibility::Hidden);

	int energy = PeppyTurnWidget->PeppySkillTableRows[tablecancelNum]->Cost;
	PeppyTurnWidget->MinusEnergy(energy);
}

void UPeppyTurn_SelectedUI_Widget::OnHovered_SelectedSkill()
{
	FString skilliconname = "";
	int selectedUINum = 0;
	for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
		if (PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->GetVisibility() == ESlateVisibility::Visible && PeppyTurnWidget->SelectedUIListArr[i] == this) {
			selectedUINum = i;
			skilliconname = PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString();
			break;
		}
	}

	for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
		if (skilliconname == PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush.GetResourceName().ToString())
		{
			PeppyTurnWidget->SkillListFormRef->CreateHoverWidget(i, (UUserWidget*)PeppyTurnWidget->SelectedUIListArr[selectedUINum]->BP_PeppyTurnIcon->Image_SelectedSkillIcon, true);
			break;
		}
	}
}

void UPeppyTurn_SelectedUI_Widget::OnClick_CancelSkill()
{
	for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
		if (PeppyTurnWidget->SelectedUIListArr[i]->Button_Cancel == this->Button_Cancel) {
			FString iconname = PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString();
			int cancelNum = *BattleManagerSystem->SkillIconRowMap.Find(iconname);
			CancelSkill(cancelNum, PeppyTurnWidget->SkillListFormRef->SkillHoverWidgetRef);
			break;
		}
	}
}