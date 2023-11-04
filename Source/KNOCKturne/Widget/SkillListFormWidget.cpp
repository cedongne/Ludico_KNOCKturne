// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

#include "PackageSkillWidget.h"
#include "Pac_SelectedUI_Widget.h"

void USkillListFormWidget::NativePreConstruct() {
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_CheckBox = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox"));
	Image_Energy = (UImage*)GetWidgetFromName(TEXT("Image_Energy"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_IconBackground = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground"));
	Image_Stance = (UImage*)GetWidgetFromName(TEXT("Image_Stance"));
	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_SkillName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_Stance = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Stance"));
}

void USkillListFormWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &USkillListFormWidget::OnClicked_Skill);
	}
}

void USkillListFormWidget::OnClicked_Skill() {
	if (PackageSkillWidget->SelectedUIListArr[7]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden)
	{
		for (int i = 0; i < PackageSkillWidget->SkillListArr.Num(); i++) {
			if (PackageSkillWidget->SkillListArr[i]->Button_Background == this->Button_Background && PackageSkillWidget->SkillListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
				PackageSkillWidget->SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
				SelectedSkillImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SkillListArr[i]->Image_Icon->Brush);
				AddSkillInSelectedUI();
			}
		}
	}
	else {
		
		for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
			if (PackageSkillWidget->SelectedUIListArr[i]->SkillError) {
				NTLOG(Warning, TEXT("skillerror!"));
				PlayAnimation(PackageSkillWidget->SelectedUIListArr[i]->SkillError);
			}
			
		}
	}
}

void USkillListFormWidget::AddSkillInSelectedUI() {
	for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
		if (PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
			PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->SetBrushFromTexture(SelectedSkillImg);
			PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->SetVisibility(ESlateVisibility::Visible);
			PackageSkillWidget->SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
}