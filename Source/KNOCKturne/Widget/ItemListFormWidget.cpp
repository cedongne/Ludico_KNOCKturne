// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemListFormWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

UItemListFormWidget::UItemListFormWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	SkillDescriptionComponent = CreateDefaultSubobject<USkillDescriptionComponent>(TEXT("SkillDescriptionComponent"));
}

void UItemListFormWidget::NativePreConstruct()
{
}

void UItemListFormWidget::NativeConstruct()
{
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &UItemListFormWidget::OnClick_Item);
		Button_Background->OnHovered.AddDynamic(this, &UItemListFormWidget::OnHovered_Item);
	}
}

void UItemListFormWidget::SelectItem(int clickedNum, UItemHoverWidget* ItemHover)
{
	for (int i = 0; i < PackageSkillWidget->ItemListArr.Num(); i++) {
		if (i == clickedNum && KNOCKturneGameState->ItemCountList[i] > 0) {
			if (PackageSkillWidget->ItemListArr[i]->Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
				PackageSkillWidget->ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
				UTexture2D* selectedimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->ItemListArr[i]->Image_Icon->Brush);
				PackageSkillWidget->Selected_Item->Image_Icon->SetBrushFromTexture(selectedimg);

				if (ItemHover) {
					ItemHover->Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
				}

				if (PackageSkillWidget->Selected_Item->Image_Icon->GetVisibility() == ESlateVisibility::Hidden) {
					PackageSkillWidget->Selected_Item->Image_Icon->SetVisibility(ESlateVisibility::Visible);
					PackageSkillWidget->Selected_Item->Button_Cancel->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else {
				PackageSkillWidget->Selected_Item->CancelItem(ItemHover);
				break;
			}
		}
		else {
			PackageSkillWidget->ItemListArr[i]->Image_CheckBox->SetBrushFromTexture(icon_checkbox);
		}
	}
}

void UItemListFormWidget::OnClick_Item()
{
	for (int i = 0; i < PackageSkillWidget->ItemListArr.Num(); i++) {
		if (PackageSkillWidget->ItemListArr[i]->Button_Background == this->Button_Background) {
			SelectItem(i, ItemHoverWidgetRef);
			break;
		}
	}
}

void UItemListFormWidget::CreateHoverWidget(int hoveredNum, UButton* backgroundBtn, bool isSelectedUI)
{
	/*if (ItemHoverWidgetRef) {
		if (!ItemHoverWidgetRef->IsInViewport()) {
			if (ItemHoverClass) {
				ItemHoverWidgetRef = CreateWidget<UItemHoverWidget>(GetWorld(), ItemHoverClass);
				if (ItemHoverWidgetRef) {
					ItemHoverWidgetRef->AddToViewport();
				}
			}
		}
	}
	else {
		if (ItemHoverClass) {
			ItemHoverWidgetRef = CreateWidget<UItemHoverWidget>(GetWorld(), ItemHoverClass);
			if (ItemHoverWidgetRef) {
				ItemHoverWidgetRef->AddToViewport();
			}
		}
	}*/

	if (!ItemHoverWidgetRef || !ItemHoverWidgetRef->IsInViewport()) {
		if (ItemHoverClass) {
			ItemHoverWidgetRef = CreateWidget<UItemHoverWidget>(GetWorld(), ItemHoverClass);
			if (ItemHoverWidgetRef) {
				ItemHoverWidgetRef->AddToViewport();
			}
		}
	}

	if (!isSelectedUI && ItemHoverWidgetRef) {
		ItemHoverWidgetRef->Button_Background->OnClicked.AddDynamic(ItemHoverWidgetRef, &UItemHoverWidget::OnClick_Button);
	}

	ItemHoverWidgetRef->Image_CheckBox->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->ItemListArr[hoveredNum]->Image_CheckBox->Brush));
	ItemHoverWidgetRef->Image_Icon->SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->ItemListArr[hoveredNum]->Image_Icon->Brush));
	ItemHoverWidgetRef->TextBlock_SkillName->SetText(PackageSkillWidget->ItemListArr[hoveredNum]->TextBlock_SkillName->GetText());
	ItemHoverWidgetRef->TextBlock_Count->SetText(PackageSkillWidget->ItemListArr[hoveredNum]->TextBlock_Count->GetText());
	ItemHoverWidgetRef->TextBlock_Description->SetText(FText::FromString(SkillDescriptionComponent->ItemRedefineDescription(hoveredNum)));
	SkillDescriptionComponent->SetHoverWidgetPos(ItemHoverWidgetRef, (UUserWidget*)PackageSkillWidget->ItemListArr[hoveredNum]->Button_Background);

	if (isSelectedUI) {
		SkillDescriptionComponent->SetSelectedSkillHoverPos(ItemHoverWidgetRef, (UUserWidget*)backgroundBtn);
	}
	else {
		SkillDescriptionComponent->SetHoverWidgetPos(ItemHoverWidgetRef, (UUserWidget*)backgroundBtn);
	}
}

void UItemListFormWidget::OnHovered_Item() {
	for (int i = 0; i < PackageSkillWidget->ItemListArr.Num(); i++) {
		if (PackageSkillWidget->ItemListArr[i]->Button_Background == this->Button_Background) {
			CreateHoverWidget(i, PackageSkillWidget->ItemListArr[i]->Button_Background, false);
			break;
		}
	}
}