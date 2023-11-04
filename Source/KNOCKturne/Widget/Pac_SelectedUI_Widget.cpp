// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Pac_SelectedUI_Widget.h"
#include "PackageSkillWidget.h"
#include "SkillListFormWidget.h"
#include "ItemListFormWidget.h"
#include "SpecialtyListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UPac_SelectedUI_Widget::NativePreConstruct() {
	Super::NativePreConstruct();

	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Button_Cancel = (UButton*)GetWidgetFromName(TEXT("Button_Cancel"));
}

void UPac_SelectedUI_Widget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Cancel) {
		Button_Cancel->OnClicked.AddDynamic(this, &UPac_SelectedUI_Widget::OnClick_Cancel);
	}
}

void UPac_SelectedUI_Widget::OnClick_Cancel() {
	if (PackageSkillWidget->UniformGridPanel_Skill->GetVisibility() == ESlateVisibility::Visible) {
		CancelSkill();
	}
	else if (PackageSkillWidget->UniformGridPanel_Specialty->GetVisibility() == ESlateVisibility::Visible) {
		CancelSpecialty();
	}
	else if (PackageSkillWidget->UniformGridPanel_Item->GetVisibility() == ESlateVisibility::Visible) {
		CancelItem();
	}
}

void UPac_SelectedUI_Widget::CancelSkill()
{
	int cancelIdx = 0;

	for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
		if (PackageSkillWidget->SelectedUIListArr[i]->Button_Cancel == this->Button_Cancel) {
			cancelIdx = i;
			cancelimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->Brush);
			break;
		}
	}

	if ((cancelIdx == PackageSkillWidget->SelectedUIListArr.Num() - 1) || (PackageSkillWidget->SelectedUIListArr[cancelIdx + 1]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden)) {
		PackageSkillWidget->SelectedUIListArr[cancelIdx]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
		PackageSkillWidget->SelectedUIListArr[cancelIdx]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		for (int j = cancelIdx; j < PackageSkillWidget->SelectedUIListArr.Num() - 1; j++) {
			// 다음 칸이 비어있지 않으면
			if (PackageSkillWidget->SelectedUIListArr[j + 1]->Image_Icon->GetVisibility() == ESlateVisibility::Visible) {
				PackageSkillWidget->SelectedUIListArr[j]->Image_Icon->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SelectedUIListArr[j + 1]->Image_Icon->Brush));

				if (j + 1 == PackageSkillWidget->SelectedUIListArr.Num() - 1) {
					PackageSkillWidget->SelectedUIListArr[j + 1]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
					PackageSkillWidget->SelectedUIListArr[j + 1]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			// 다음 칸이 비어있으면
			else {
				PackageSkillWidget->SelectedUIListArr[j]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
				PackageSkillWidget->SelectedUIListArr[j]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
				break;
			}
		}
	}

	for (int k = 0; k < PackageSkillWidget->SkillListArr.Num(); k++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SkillListArr[k]->Image_Icon->Brush) == cancelimg) {
			PackageSkillWidget->SkillListArr[k]->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->SkillListFormRef->icon_checkbox);
		}
	}
}

void UPac_SelectedUI_Widget::CancelSpecialty()
{
	PackageSkillWidget->Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	PackageSkillWidget->Selected_Specialty->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < PackageSkillWidget->SpecialtyListArr.Num(); i++) {
		if (PackageSkillWidget->Selected_Specialty->Image_Icon->Brush.GetResourceName() == PackageSkillWidget->SpecialtyListArr[i]->Image_Icon->Brush.GetResourceName()) {
			PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->SpecialtyListFormRef->icon_checkbox);
		}
	}
}

void UPac_SelectedUI_Widget::CancelItem()
{
	PackageSkillWidget->Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	PackageSkillWidget->Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < PackageSkillWidget->ItemListArr.Num(); i++) {
		if (PackageSkillWidget->Selected_Item->Image_Icon->Brush.GetResourceName() == PackageSkillWidget->ItemListArr[i]->Image_Icon->Brush.GetResourceName()) {
			PackageSkillWidget->ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->ItemListFormRef->icon_checkbox);
		}
	}
}
