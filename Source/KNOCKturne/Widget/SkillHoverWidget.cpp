// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillHoverWidget.h"
#include "PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void USkillHoverWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	if (PackageSkillWidgetArr.Num() > 0 && (UPackageSkillWidget*)PackageSkillWidgetArr[0]) {
		PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];
	}

	Button_Background->OnUnhovered.AddDynamic(this, &USkillHoverWidget::Remove);
}

void USkillHoverWidget::OnClick_Button()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		PackageSkillWidget->SkillListFormRef->SelectSkill(FindInteractionNum(), this);
	}
	else {
		PackageSkillWidget->SelectedUIRef->CancelSkill(FindInteractionNum(), this);
	}
}

int32 USkillHoverWidget::FindInteractionNum()
{
	for (int i = 0; i < PackageSkillWidget->PeppySkillTableRows.Num(); i++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(Image_Icon->Brush) == PackageSkillWidget->PeppySkillTableRows[i]->SkillIcon) {
			return i;
		}
	}

	NTLOG(Warning, TEXT("FindInteractionNum is NULL!"));
	return 100;
}

void USkillHoverWidget::Remove()
{
	RemoveFromParent();
}

void USkillHoverWidget::RemoveSelectedHoverWidget(UButton* SelectedSkillBtn)
{
	if (this->Button_Background->IsHovered() == false && SelectedSkillBtn->IsHovered() == false) {
		RemoveFromParent();
	}
}
