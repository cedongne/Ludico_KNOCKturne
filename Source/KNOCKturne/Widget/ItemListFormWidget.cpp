// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UItemListFormWidget::NativePreConstruct()
{

}

void UItemListFormWidget::NativeConstruct()
{
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &UItemListFormWidget::OnClicked_Item);
	}
}

void UItemListFormWidget::OnClicked_Item()
{
	for (int i = 0; i < PackageSkillWidget->ItemListArr.Num(); i++) {
		if (PackageSkillWidget->ItemListArr[i]->Button_Background == this->Button_Background && KNOCKturneGameState->ItemCountList[i] > 0) {
			if (PackageSkillWidget->ItemListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
				PackageSkillWidget->ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
				UTexture2D* selectedimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->ItemListArr[i]->Image_Icon->Brush);
				PackageSkillWidget->Selected_Item->Image_Icon->SetBrushFromTexture(selectedimg);

				if (PackageSkillWidget->Selected_Item->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
					PackageSkillWidget->Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Visible);
					PackageSkillWidget->Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else {
				PackageSkillWidget->Selected_Item->CancelItem();
				break;
			}
		}
		else {
			PackageSkillWidget->ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
		}
	}
}
