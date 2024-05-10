// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PackageSkillCardWidget.h"
#include "GameMode/PeppyController.h"
#include "PackageWidget.h"
#include "PackageSkillHoverWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UPackageSkillCardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_Stance = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Stance"));
}

void UPackageSkillCardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Background) {
		Button_Background->OnHovered.AddDynamic(this, &UPackageSkillCardWidget::CreateSkillHoverWidget);
	}
}

int32 UPackageSkillCardWidget::GetCardSkillRowNum()
{
	return BattleManagerSystem->FindSkillRow(Image_Icon->Brush.GetResourceName().ToString());
}

void UPackageSkillCardWidget::CreateSkillHoverWidget()
{
	TArray<UUserWidget*> AllPackageWidgetArr;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, AllPackageWidgetArr, PackageWidgetClass);
	if (AllPackageWidgetArr.Num() > 0) {
		PackageWidget = (UPackageWidget*)AllPackageWidgetArr[0];

		if (PackageWidget->isScrolling) {
			return;
		}
	}

	bool isSelected;
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox")
		isSelected = false;
	else
		isSelected = true;

	class UPackageSkillHoverWidget* SkillCardHoverWidget;
	if (SkillCardHoverWidgetClass) {
		SkillCardHoverWidget = CreateWidget<UPackageSkillHoverWidget>(GetWorld(), SkillCardHoverWidgetClass);
		if (SkillCardHoverWidget) {
			SkillCardHoverWidget->AddToViewport();
			SkillCardHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(SkillCardHoverWidget);
			SkillCardHoverWidget->SetHoverWidgetUI(GetCardSkillRowNum(), isSelected);
		}
	}
}
