// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UItemListFormWidget::NativePreConstruct()
{

}

void UItemListFormWidget::NativeConstruct()
{
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &UItemListFormWidget::OnClicked_Skill);
	}
}

void UItemListFormWidget::OnClicked_Skill()
{

}
