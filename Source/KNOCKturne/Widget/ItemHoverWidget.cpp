// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemHoverWidget.h"
#include "PackageSkillWidget.h"
#include "ItemListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UItemHoverWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	if (PackageSkillWidgetArr.Num() > 0 && (UPackageSkillWidget*)PackageSkillWidgetArr[0]) {
		PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];
	}

	Button_Background->OnUnhovered.AddDynamic(this, &UItemHoverWidget::Remove);
}

void UItemHoverWidget::OnClick_Button()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		PackageSkillWidget->ItemListFormRef->SelectItem(FindInteractionNum(), this);
	}
	else {
		PackageSkillWidget->SelectedUIRef->CancelItem(this);
	}
}

int32 UItemHoverWidget::FindInteractionNum()
{
	for (int i = 0; i < PackageSkillWidget->ItemTableRows.Num(); i++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(Image_Icon->Brush) == PackageSkillWidget->ItemTableRows[i]->ItemIcon) {
			return i;
		}
	}

	NTLOG(Warning, TEXT("FindInteractionNum is NULL!"));
	return 100;
}

void UItemHoverWidget::Remove()
{
	RemoveFromParent();
}