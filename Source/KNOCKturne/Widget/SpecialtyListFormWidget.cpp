// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SpecialtyListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>


void USpecialtyListFormWidget::NativePreConstruct()
{
	
}

void USpecialtyListFormWidget::NativeConstruct()
{
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &USpecialtyListFormWidget::OnClicked_Specialty);
	}
}

void USpecialtyListFormWidget::OnClicked_Specialty()
{
	for (int i = 0; i < PackageSkillWidget->SpecialtyListArr.Num(); i++) {
		if (PackageSkillWidget->SpecialtyListArr[i]->Button_Background == this->Button_Background) {
			PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
			UTexture2D* selectedimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SpecialtyListArr[i]->Image_Icon->Brush);
			PackageSkillWidget->Selected_Specialty->Image_Icon->SetBrushFromTexture(selectedimg);

			if (PackageSkillWidget->Selected_Specialty->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
				PackageSkillWidget->Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Visible);
				PackageSkillWidget->Selected_Specialty->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else {
			PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
		}
	}
}
