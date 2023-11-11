// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillHoverWidget.h"
#include "PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurnWidget.h"

void USkillHoverWidget::NativeConstruct() {
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
		if (PackageSkillWidgetArr.Num() > 0 && (UPackageSkillWidget*)PackageSkillWidgetArr[0]) {
			PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];
		}
	}
	else if (GetWorld()->GetMapName() == "UEDPIE_0_LV_Battle") {
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
		PeppyTurnWidget = (UPeppyTurnWidget*)PeppyTurnWidgetArr[0];
	}

	Button_Background->OnUnhovered.AddDynamic(this, &USkillHoverWidget::Remove);
}

void USkillHoverWidget::OnClick_Button()
{
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
			PackageSkillWidget->SkillListFormRef->SelectSkill(FindInteractionNum(), this);
		}
		else {
			PackageSkillWidget->SelectedUIRef->CancelSkill(FindInteractionNum(), this);
		}
	}
	else if (GetWorld()->GetMapName() == "UEDPIE_0_Battle") {
		if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
			PeppyTurnWidget->SkillListFormRef->SelectSkill(FindInteractionNum(), this);
		}
		else {
			//PeppyTurnWidget->SelectedUIRef->CancelSkill(FindInteractionNum(), this);
		}
	}
}

int32 USkillHoverWidget::FindInteractionNum()
{
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		for (int i = 0; i < PackageSkillWidget->PeppySkillTableRows.Num(); i++) {
			if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(Image_Icon->Brush) == PackageSkillWidget->PeppySkillTableRows[i]->SkillIcon) {
				return i;
			}
		}
	}
	else if (GetWorld()->GetMapName() == "UEDPIE_0_Battle") {
		for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
			if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(Image_Icon->Brush) == UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush)) {
				return i;
			}
		}
	}

	NTLOG(Warning, TEXT("FindInteractionNum is NULL!"));
	return 100;
}

void USkillHoverWidget::Remove()
{
	RemoveFromParent();
}
