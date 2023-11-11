// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SpecialtyHoverWidget.h"
#include "PackageSkillWidget.h"
#include "SpecialtyListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void USpecialtyHoverWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	Button_Background->OnUnhovered.AddDynamic(this, &USpecialtyHoverWidget::Remove);
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

void USpecialtyHoverWidget::Remove()
{
	RemoveFromParent();
}
