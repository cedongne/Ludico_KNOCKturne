// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SpecialtyListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

USpecialtyListFormWidget::USpecialtyListFormWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SkillDescriptionComponent = CreateDefaultSubobject<USkillDescriptionComponent>(TEXT("SkillDescriptionComponent"));
}

void USpecialtyListFormWidget::NativePreConstruct()
{
}

void USpecialtyListFormWidget::NativeConstruct()
{
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &USpecialtyListFormWidget::OnClick_Specialty);
		Button_Background->OnHovered.AddDynamic(this, &USpecialtyListFormWidget::OnHovered_Specialty);
	}
}

void USpecialtyListFormWidget::SelectSpecialty(int clickedNum, USpecialtyHoverWidget* SpecialtyHover)
{
	for (int i = 0; i < PackageSkillWidget->SpecialtyListArr.Num(); i++) {
		if (i == clickedNum) {
			if (PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
				PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
				UTexture2D* selectedimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SpecialtyListArr[i]->Image_Icon->Brush);
				PackageSkillWidget->Selected_Specialty->Image_Icon->SetBrushFromTexture(selectedimg);
				SpecialtyHover->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);

				if (PackageSkillWidget->Selected_Specialty->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
					PackageSkillWidget->Selected_Specialty->Image_Icon->SetVisibility(ESlateVisibility::Visible);
					PackageSkillWidget->Selected_Specialty->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else {
				PackageSkillWidget->Selected_Specialty->CancelSpecialty(SpecialtyHover);
				break;
			}
		}
		else {
			PackageSkillWidget->SpecialtyListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
			if (SpecialtyHover) {
				SpecialtyHover->Image_CheckBox->SetBrushFromTexture(icon_checkbox);

			}
		}
	}
}

void USpecialtyListFormWidget::OnClick_Specialty()
{
	for (int i = 0; i < PackageSkillWidget->SpecialtyListArr.Num(); i++) {
		if (PackageSkillWidget->SpecialtyListArr[i]->Button_Background == this->Button_Background) {
			SelectSpecialty(i, SpecialtyHoverWidgetRef);
			break;
		}
	}
}

void USpecialtyListFormWidget::OnHovered_Specialty() {
	int hoveredNum = 0;

	for (int i = 0; i < PackageSkillWidget->SpecialtyListArr.Num(); i++) {
		if (PackageSkillWidget->SpecialtyListArr[i]->Button_Background == this->Button_Background) {
			hoveredNum = i;
			break;
		}
	}

	if (SpecialtyHoverWidgetRef) {
		if (!SpecialtyHoverWidgetRef->IsInViewport()) {
			if (SpecialtyHoverClass) {
				SpecialtyHoverWidgetRef = CreateWidget<USpecialtyHoverWidget>(GetWorld(), SpecialtyHoverClass);
				if (SpecialtyHoverWidgetRef) {
					SpecialtyHoverWidgetRef->AddToViewport();
				}
			}
		}
	}
	else {
		if (SpecialtyHoverClass) {
			SpecialtyHoverWidgetRef = CreateWidget<USpecialtyHoverWidget>(GetWorld(), SpecialtyHoverClass);
			if (SpecialtyHoverWidgetRef) {
				SpecialtyHoverWidgetRef->AddToViewport();
			}
		}
	}

	SpecialtyHoverWidgetRef->Image_CheckBox->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SpecialtyListArr[hoveredNum]->Image_CheckBox->Brush));
	SpecialtyHoverWidgetRef->Image_Icon->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SpecialtyListArr[hoveredNum]->Image_Icon->Brush));
	SpecialtyHoverWidgetRef->TextBlock_CoolTimeSec->SetText(PackageSkillWidget->SpecialtyListArr[hoveredNum]->TextBlock_CoolTimeSec->GetText());
	SpecialtyHoverWidgetRef->TextBlock_SkillName->SetText(PackageSkillWidget->SpecialtyListArr[hoveredNum]->TextBlock_SkillName->GetText());
	SpecialtyHoverWidgetRef->TextBlock_Energy->SetText(PackageSkillWidget->SpecialtyListArr[hoveredNum]->TextBlock_Energy->GetText());
	SpecialtyHoverWidgetRef->TextBlock_Description->SetText(FText::FromString(SkillDescriptionComponent->SpecialtyRedefineDescription(hoveredNum)));
	SkillDescriptionComponent->SetHoverWidgetPos(SpecialtyHoverWidgetRef, PackageSkillWidget->SpecialtyListArr[hoveredNum]->Button_Background);
}