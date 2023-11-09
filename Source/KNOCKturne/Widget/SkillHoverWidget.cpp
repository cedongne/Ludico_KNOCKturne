// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillHoverWidget.h"
#include "PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void USkillHoverWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &USkillHoverWidget::OnClick_Button);
	}
}

void USkillHoverWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds) {
	Super::NativeTick(Geometry, DeltaSeconds);

	if (!IsHovered()) {
		if (PackageSkillWidget->SkillListArr[FindInteractionNum()]->Button_Background->IsHovered() == false) {
			RemoveFromParent();
		}
	}
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
