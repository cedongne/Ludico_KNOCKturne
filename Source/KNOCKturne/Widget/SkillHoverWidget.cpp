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
		RemoveFromParent();
	}
}

void USkillHoverWidget::OnClick_Button()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		PackageSkillWidget->SkillListFormRef->SelectSkill(PackageSkillWidget->SkillListFormRef->hoveredNum);
	}
	else {
		PackageSkillWidget->SelectedUIRef->CancelSkill(PackageSkillWidget->SkillListFormRef->hoveredNum);
	}
}