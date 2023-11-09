// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SpecialtyHoverWidget.h"
#include "PackageSkillWidget.h"
#include "SpecialtyListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void USpecialtyHoverWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &USpecialtyHoverWidget::OnClick_Button);
	}
}

void USpecialtyHoverWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds) {
	Super::NativeTick(Geometry, DeltaSeconds);

	if (!IsHovered()) {
		RemoveFromParent();
	}
}

void USpecialtyHoverWidget::OnClick_Button()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		PackageSkillWidget->SpecialtyListFormRef->SelectSpecialty(FindInteractionNum(), this);
	}
	else {
		PackageSkillWidget->SelectedUIRef->CancelSpecialty(this);
	}
}

int32 USpecialtyHoverWidget::FindInteractionNum()
{
	for (int i = 0; i < PackageSkillWidget->SpecialSkillTableRows.Num(); i++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(Image_Icon->Brush) == PackageSkillWidget->SpecialSkillTableRows[i]->SpecialSkillIcon) {
			return i;
		}
	}

	NTLOG(Warning, TEXT("FindInteractionNum is NULL!"));
	return 100;
}
