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
		OnClick_CancelSkill();
	}
	else if (PackageSkillWidget->UniformGridPanel_Specialty->GetVisibility() == ESlateVisibility::Visible) {
		CancelSpecialty(PackageSkillWidget->SpecialtyListFormRef->SpecialtyHoverWidgetRef);
	}
	else if (PackageSkillWidget->UniformGridPanel_Item->GetVisibility() == ESlateVisibility::Visible) {
		CancelItem(PackageSkillWidget->ItemListFormRef->ItemHoverWidgetRef);
	}
}

void UPac_SelectedUI_Widget::CancelSkill(int cancelNum, USkillHoverWidget* SkillHover)
{
	for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
		if (i == cancelNum) {
			cancelimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->Brush);
			break;
		}
	}

	if ((cancelNum == PackageSkillWidget->SelectedUIListArr.Num() - 1) || (PackageSkillWidget->SelectedUIListArr[cancelNum + 1]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden)) {
		PackageSkillWidget->SelectedUIListArr[cancelNum]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
		PackageSkillWidget->SelectedUIListArr[cancelNum]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		for (int j = cancelNum; j < PackageSkillWidget->SelectedUIListArr.Num() - 1; j++) {
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
			SkillHover->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->SkillListFormRef->icon_checkbox);
		}
	}
}

void UPac_SelectedUI_Widget::OnClick_CancelSkill()
{
	for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
		if (PackageSkillWidget->SelectedUIListArr[i]->Button_Cancel == this->Button_Cancel) {
			CancelSkill(i, PackageSkillWidget->SkillListFormRef->SkillHoverWidgetRef);
		}
	}
}

void UPac_SelectedUI_Widget::CancelSpecialty(USpecialtyHoverWidget* SpecialtyHover)
{
	PackageSkillWidget->Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	PackageSkillWidget->Selected_Specialty->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < PackageSkillWidget->SpecialtyListArr.Num(); i++) {
		if (PackageSkillWidget->Selected_Specialty->Image_Icon->Brush.GetResourceName() == PackageSkillWidget->SpecialtyListArr[i]->Image_Icon->Brush.GetResourceName()) {
			PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->SpecialtyListFormRef->icon_checkbox);
			SpecialtyHover->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->SpecialtyListFormRef->icon_checkbox);
		}
	}
}

void UPac_SelectedUI_Widget::CancelItem(UItemHoverWidget* ItemHover)
{
	PackageSkillWidget->Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	PackageSkillWidget->Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < PackageSkillWidget->ItemListArr.Num(); i++) {
		if (PackageSkillWidget->Selected_Item->Image_Icon->Brush.GetResourceName() == PackageSkillWidget->ItemListArr[i]->Image_Icon->Brush.GetResourceName()) {
			PackageSkillWidget->ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->ItemListFormRef->icon_checkbox);
			ItemHover->Image_CheckBox->SetBrushFromTexture(PackageSkillWidget->ItemListFormRef->icon_checkbox);
		}
	}
}