// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

#include "PackageSkillWidget.h"
#include "Pac_SelectedUI_Widget.h"
#include "PeppyTurn_SelectedUI_Widget.h"
#include "PeppyTurn_SelectedIcon_Widget.h"

USkillListFormWidget::USkillListFormWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SkillDescriptionComponent = CreateDefaultSubobject<USkillDescriptionComponent>(TEXT("SkillDescriptionComponent"));
}

void USkillListFormWidget::NativePreConstruct() {
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_CheckBox = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_IconBackground = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground"));
	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_SkillName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_Stance = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Stance"));
}

void USkillListFormWidget::NativeConstruct() {
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
		PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];
	}
	else if (GetWorld()->GetMapName() == "UEDPIE_0_LV_Battle") {
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
		PeppyTurnWidget = (UPeppyTurnWidget*)PeppyTurnWidgetArr[0];
	}

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &USkillListFormWidget::OnClick_Skill);
		Button_Background->OnHovered.AddDynamic(this, &USkillListFormWidget::OnHovered_Skill);
	}
}

void USkillListFormWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds) {
	Super::NativeTick(Geometry, DeltaSeconds);

}

void USkillListFormWidget::SelectSkill(int clickedNum, USkillHoverWidget* SkillHover) {
	// 허브월드
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		if (PackageSkillWidget->SelectedUIListArr[7]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden)
		{
			for (int i = 0; i < PackageSkillWidget->SkillListArr.Num(); i++) {
				if (i == clickedNum && PackageSkillWidget->SkillListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
					PackageSkillWidget->SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
					SelectedSkillImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SkillListArr[i]->Image_Icon->Brush);

					if (SkillHover) {
						SkillHover->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
					}
					else {
						NTLOG(Warning, TEXT("SkillHoverWidget is NULL!"));
					}
					AddSkillInSelectedUI();
					break;
				}
			}
		}
		else {
			for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
				if (PackageSkillWidget->SelectedUIListArr[i]->SkillError) {
					NTLOG(Warning, TEXT("skillerror!"));
					//PlayAnimation(PackageSkillWidget->SelectedUIListArr[i]->SkillError);
					PackageSkillWidget->SelectedUIListArr[i]->PlaySkillErrorAnim();
				}

			}
		}
	}
	
	// 전투 레벨
	else if (GetWorld()->GetMapName() == "UEDPIE_0_LV_Battle") {
		if (PeppyTurnWidget->SelectedUIListArr[3]->Image_NumBackground->GetVisibility() == ESlateVisibility::Hidden) {
			for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
				if (i == clickedNum && PeppyTurnWidget->SkillListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
					PeppyTurnWidget->SkillListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
					SelectedSkillImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush);

					if (SkillHover) {
						SkillHover->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
					}
					
					AddSkillInSelectedUI();
					break;
				}
			}
		}
		else {
			for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
				PeppyTurnWidget->SelectedUIListArr[i]->PlaySkillErrorAnim();
			}
		}
	}
}

void USkillListFormWidget::OnClick_Skill()
{
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		for (int i = 0; i < PackageSkillWidget->SkillListArr.Num(); i++) {
			if (PackageSkillWidget->SkillListArr[i]->Button_Background == this->Button_Background) {
				if (PackageSkillWidget->SkillListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
					SelectSkill(i, SkillHoverWidgetRef);
				}
				else {
					PackageSkillWidget->SelectedUIRef->CancelSkill(i, SkillHoverWidgetRef);
				}
				break;
			}
		}
	}
	else if (GetWorld()->GetMapName() == "UEDPIE_0_LV_Battle") {
		for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
			if (PeppyTurnWidget->SkillListArr[i]->Button_Background == this->Button_Background) {
				if (PeppyTurnWidget->SkillListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
					SelectSkill(i, SkillHoverWidgetRef);
				}
				else {
					//PeppyTurnWidget->SelectedUIRef->CancelSkill(i, SkillHoverWidgetRef);
				}
				break;
			}
		}
	}
}

void USkillListFormWidget::AddSkillInSelectedUI() {
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
			if (PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
				PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->SetBrushFromTexture(SelectedSkillImg);
				PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->SetVisibility(ESlateVisibility::Visible);
				PackageSkillWidget->SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
				break;
			}
		}
	}
	else if (GetWorld()->GetMapName() == "UEDPIE_0_LV_Battle") {
		for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
			if (PeppyTurnWidget->SelectedUIListArr[i]->Image_NumBackground->GetVisibility() == ESlateVisibility::Hidden) {
				PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(SelectedSkillImg);
				PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->SetVisibility(ESlateVisibility::Visible);
				PeppyTurnWidget->SelectedUIListArr[i]->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
				PeppyTurnWidget->SelectedUIListArr[i]->Image_NumBackground->SetVisibility(ESlateVisibility::Visible);
				PeppyTurnWidget->SelectedUIListArr[i]->TextBlock_SelectNum->SetVisibility(ESlateVisibility::Visible);
				break;
			}
		}
	}
}

void USkillListFormWidget::CreateHoverWidget(int hoveredNum, UButton* backgroundBtn, bool isSelectedUI)
{
	/*if (SkillHoverWidgetRef) {
		if (!SkillHoverWidgetRef->IsInViewport()) {
			if (SkillHoverClass) {
				SkillHoverWidgetRef = CreateWidget<USkillHoverWidget>(GetWorld(), SkillHoverClass);
				if (SkillHoverWidgetRef) {
					SkillHoverWidgetRef->AddToViewport();
				}
			}
		}
	}*/
	if (!SkillHoverWidgetRef || !SkillHoverWidgetRef->IsInViewport()) {
		if (SkillHoverClass) {
			SkillHoverWidgetRef = CreateWidget<USkillHoverWidget>(GetWorld(), SkillHoverClass);
			if (SkillHoverWidgetRef) {
				SkillHoverWidgetRef->AddToViewport();
			}
		}
	}

	if (!isSelectedUI && SkillHoverWidgetRef) {
		SkillHoverWidgetRef->Button_Background->OnClicked.AddDynamic(SkillHoverWidgetRef, &USkillHoverWidget::OnClick_Button);
	}

	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		SkillHoverWidgetRef->Image_CheckBox->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SkillListArr[hoveredNum]->Image_CheckBox->Brush));
		SkillHoverWidgetRef->Image_Icon->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SkillListArr[hoveredNum]->Image_Icon->Brush));
		SkillHoverWidgetRef->TextBlock_CoolTimeSec->SetText(PackageSkillWidget->SkillListArr[hoveredNum]->TextBlock_CoolTimeSec->GetText());
		SkillHoverWidgetRef->TextBlock_SkillName->SetText(PackageSkillWidget->SkillListArr[hoveredNum]->TextBlock_SkillName->GetText());
		SkillHoverWidgetRef->TextBlock_Energy->SetText(PackageSkillWidget->SkillListArr[hoveredNum]->TextBlock_Energy->GetText());
		SkillHoverWidgetRef->TextBlock_Stance->SetText(PackageSkillWidget->SkillListArr[hoveredNum]->TextBlock_Stance->GetText());
		SkillHoverWidgetRef->TextBlock_Description->SetText(FText::FromString(SkillDescriptionComponent->SkillRedefineDescription(hoveredNum)));

		if (isSelectedUI) {
			SkillDescriptionComponent->SetSelectedSkillHoverPos(SkillHoverWidgetRef, backgroundBtn);
		}
		else {
			SkillDescriptionComponent->SetHoverWidgetPos(SkillHoverWidgetRef, backgroundBtn);
		}
	}

	
}

void USkillListFormWidget::OnHovered_Skill()
{
	if (GetWorld()->GetMapName() == "UEDPIE_0_LV_HubWorld") {
		for (int i = 0; i < PackageSkillWidget->SkillListArr.Num(); i++) {
			if (PackageSkillWidget->SkillListArr[i]->Button_Background == this->Button_Background) {
				CreateHoverWidget(i, PackageSkillWidget->SkillListArr[i]->Button_Background, false);
				break;
			}
		}
	}
	
}