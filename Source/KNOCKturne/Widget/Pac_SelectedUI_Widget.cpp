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
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageSkillWidgetArr, PackageSkillWidgetClass);
	PackageSkillWidget = (UPackageSkillWidget*)PackageSkillWidgetArr[0];

	Button_Cancel->OnClicked.AddDynamic(this, &UPac_SelectedUI_Widget::OnClick_Cancel);
	Button_Background->OnHovered.AddDynamic(this, &UPac_SelectedUI_Widget::OnHovered_SelectedSkill);
}

void UPac_SelectedUI_Widget::OnClick_Cancel() {
	/*if (PackageSkillWidget->UniformGridPanel_Skill->GetVisibility() == ESlateVisibility::Visible) {
		OnClick_CancelSkill();
	}
	else if (PackageSkillWidget->UniformGridPanel_Specialty->GetVisibility() == ESlateVisibility::Visible) {
		CancelSpecialty(PackageSkillWidget->SpecialtyListFormRef->SpecialtyHoverWidgetRef);
	}
	else if (PackageSkillWidget->UniformGridPanel_Item->GetVisibility() == ESlateVisibility::Visible) {
		CancelItem(PackageSkillWidget->ItemListFormRef->ItemHoverWidgetRef);
	}*/

	if (this->Button_Background == PackageSkillWidget->Selected_Specialty->Button_Background) {
		CancelSpecialty(PackageSkillWidget->SpecialtyListFormRef->SpecialtyHoverWidgetRef);
	}
	else if (this->Button_Background == PackageSkillWidget->Selected_Item->Button_Background) {
		CancelItem(PackageSkillWidget->ItemListFormRef->ItemHoverWidgetRef);
	}
	else {
		OnClick_CancelSkill();
	}
}

void UPac_SelectedUI_Widget::CancelSkill(int cancelNum, USkillHoverWidget* SkillHover)
{
	int cancelNuminSelectedUI = 0;
	cancelimg = PackageSkillWidget->PeppySkillTableRows[cancelNum]->SkillIcon;
	
	for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->Brush) == cancelimg) {
			cancelNuminSelectedUI = i;
			break;
		}
	}

	if ((cancelNuminSelectedUI == PackageSkillWidget->SelectedUIListArr.Num() - 1) || (PackageSkillWidget->SelectedUIListArr[cancelNuminSelectedUI + 1]->Image_Icon->GetVisibility() == ESlateVisibility::Hidden)) {
		PackageSkillWidget->SelectedUIListArr[cancelNuminSelectedUI]->Button_Cancel->SetVisibility(ESlateVisibility::Hidden);
		PackageSkillWidget->SelectedUIListArr[cancelNuminSelectedUI]->Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		for (int j = cancelNuminSelectedUI; j < PackageSkillWidget->SelectedUIListArr.Num() - 1; j++) {
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
			int cancelNum = BattleManagerSystem->FindSkillRow(PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->Brush.GetResourceName().ToString());
			CancelSkill(cancelNum, PackageSkillWidget->SkillListFormRef->SkillHoverWidgetRef);
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

void UPac_SelectedUI_Widget::OnHovered_SelectedSkill()
{
	// 선택한 특수기 호버
	if (PackageSkillWidget->Selected_Specialty->Image_Icon->GetVisibility() == ESlateVisibility::Visible && PackageSkillWidget->Selected_Specialty->Button_Background == this->Button_Background) {
		UTexture2D* skillimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->Selected_Specialty->Image_Icon->Brush);
		FString skilliconname = UKismetSystemLibrary::GetDisplayName(skillimg);
		int hoveredNum = BattleManagerSystem->FindSpecialtyRow(skilliconname);
		PackageSkillWidget->SpecialtyListFormRef->CreateHoverWidget(hoveredNum, PackageSkillWidget->Selected_Specialty->Button_Background, true);
	}
	// 선택한 아이템 호버
	else if (PackageSkillWidget->Selected_Item->Image_Icon->GetVisibility() == ESlateVisibility::Visible && PackageSkillWidget->Selected_Item->Button_Background == this->Button_Background) {
		UTexture2D* skillimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->Selected_Item->Image_Icon->Brush);
		FString skilliconname = UKismetSystemLibrary::GetDisplayName(skillimg);
		int hoveredNum = BattleManagerSystem->FindItemRow(skilliconname);
		PackageSkillWidget->ItemListFormRef->CreateHoverWidget(hoveredNum, PackageSkillWidget->Selected_Item->Button_Background, true);
	}
	// 선택한 스킬 호버
	else {
		for (int i = 0; i < PackageSkillWidget->SelectedUIListArr.Num(); i++) {
			if (PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->GetVisibility() == ESlateVisibility::Visible && PackageSkillWidget->SelectedUIListArr[i]->Button_Background == this->Button_Background) {
				UTexture2D* skillimg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PackageSkillWidget->SelectedUIListArr[i]->Image_Icon->Brush);
				FString skilliconname = UKismetSystemLibrary::GetDisplayName(skillimg);
				int hoveredNum = BattleManagerSystem->FindSkillRow(skilliconname);
				PackageSkillWidget->SkillListFormRef->CreateHoverWidget(hoveredNum, PackageSkillWidget->SelectedUIListArr[i]->Button_Background, true);
				break;
			}
		}
	}
}