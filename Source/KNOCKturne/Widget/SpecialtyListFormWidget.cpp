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
		Button_Background->OnClicked.AddDynamic(this, &USpecialtyListFormWidget::OnClicked_Skill);
	}
}

void USpecialtyListFormWidget::OnClicked_Skill()
{

}
