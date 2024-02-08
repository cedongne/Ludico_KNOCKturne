// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/CommonSkillHoverWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "CommonSkillCardWidget.h"

void UCommonSkillHoverWidget::NativePreConstruct()
{
	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_CheckBox = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_IconBackground = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground"));
	TextBlock_SkillName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName"));
	TextBlock_Description = (URichTextBlock*)GetWidgetFromName(TEXT("TextBlock_Description"));
}

void UCommonSkillHoverWidget::NativeConstruct() {
	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();

	if (Button_Background) {
		Button_Background->OnUnhovered.AddDynamic(this, &UCommonSkillHoverWidget::Remove);
		Button_Background->OnClicked.AddDynamic(this, &UCommonSkillHoverWidget::SetCheckBox);
	}
}

void UCommonSkillHoverWidget::SetHoverWidgetUI(int RowNum, bool IsSelected)
{
	NTLOG(Error, TEXT("Override the (SetHoverWidgetUI) function!"));
}

FString UCommonSkillHoverWidget::CheckValueN(int SkillIndex, float ValueN)
{
	NTLOG(Error, TEXT("Override the (CheckValueN) function!"));
	return FString();
}

FString UCommonSkillHoverWidget::CheckValueM(int SkillIndex, float ValueM)
{
	NTLOG(Error, TEXT("Override the (CheckValueM) function!"));
	return FString();
}

FString UCommonSkillHoverWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
{
	NTLOG(Error, TEXT("Override the (GetSkillIndexByKeyword) function!"));
	return FString();
}

FString UCommonSkillHoverWidget::RedefineDescription(int RowNum)
{
	NTLOG(Error, TEXT("Override the (RedefineDescription) function!"));
	return FString();
}

FString UCommonSkillHoverWidget::CheckProbability(float Probability)
{
	if (Probability != -1.0) {
		return FString::FromInt(round(Probability * 100.0));
	}
	else {
		return "None";
	}
}

void UCommonSkillHoverWidget::Remove()
{
	RemoveFromParent();
}

void UCommonSkillHoverWidget::SetCheckBox()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox")
		Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	else
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);
}