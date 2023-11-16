// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillHoverWidget.h"
#include "PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurnWidget.h"
#include "PeppyTurn_SelectedUI_Widget.h"

void USkillHoverWidget::NativeConstruct() {
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	if (PackageSkillWidgetArr.Num() > 0 && (UPackageSkillWidget*)PackageSkillWidgetArr[0]) {
		PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];
	}

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
	if (PeppyTurnWidgetArr.Num() > 0 && (UPeppyTurnWidget*)PeppyTurnWidgetArr[0]) {
		PeppyTurnWidget = (UPeppyTurnWidget*)PeppyTurnWidgetArr[0];
	}

	Button_Background->OnUnhovered.AddDynamic(this, &USkillHoverWidget::Remove);
}

void USkillHoverWidget::OnClick_Button()
{
	if (PackageSkillWidget) {
		if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
			PackageSkillWidget->SkillListFormRef->SelectSkill(FindInteractionNum(), this);
		}
		else {
			PackageSkillWidget->SelectedUIRef->CancelSkill(FindInteractionNum(), this);
		}
	}
	else if (PeppyTurnWidget) {
		if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
			PeppyTurnWidget->SkillListFormRef->SelectSkill(FindInteractionNum(), this);
		}
		else {
			PeppyTurnWidget->SelectedUIRef->CancelSkill(FindInteractionNum(), this);
		}
	}
}

int32 USkillHoverWidget::FindInteractionNum()
{
	if (BattleManagerSystem->SkillIconRowMap.Contains(Image_Icon->Brush.GetResourceName().ToString())) {
		int tablenum = *BattleManagerSystem->SkillIconRowMap.Find(Image_Icon->Brush.GetResourceName().ToString());
		return tablenum;
	}
	else {
		NTLOG(Warning, TEXT("FindInteractionNum is NULL!"));
		return NULL;
	}
}

void USkillHoverWidget::Remove()
{
	RemoveFromParent();
}
