// Fill out your copyright notice in the Description page of Project Settings.


#include "HubworldHUDWidget.h"
#include "GameInstance/KNOCKturneGameInstance.h"
#include "GameInstance/BattleManagerSystem.h"
#include "SaveExitAlertModalWidget.h"

void UHubworldHUDWidget::NativePreConstruct() {
	Button_Diary = (UButton*)GetWidgetFromName(TEXT("Button_Diary"));
	Button_Setting = (UButton*)GetWidgetFromName(TEXT("Button_Setting"));
	Button_Save = (UButton*)GetWidgetFromName(TEXT("Button_Save"));
	Image_SettingText = (UImage*)GetWidgetFromName(TEXT("Image_SettingText"));
	Image_DiaryText = (UImage*)GetWidgetFromName(TEXT("Image_DiaryText"));
	Image_SaveText = (UImage*)GetWidgetFromName(TEXT("Image_SaveText"));
	Image_DreamDiary_Updated = (UImage*)GetWidgetFromName(TEXT("Image_DreamDiary_Updated"));
}

void UHubworldHUDWidget::NativeConstruct() {
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	if (Button_Diary) {
		Button_Diary->OnClicked.AddDynamic(this, &UHubworldHUDWidget::OnClick_ButtonDiary);
	}

	if (Button_Save) {
		Button_Save->OnClicked.AddDynamic(this, &UHubworldHUDWidget::ClickSave);
	}

	if (BattleManagerSystem->isDreamDiaryUpdated) {
		Image_DreamDiary_Updated->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHubworldHUDWidget::OnClick_ButtonDiary() {
	if (DreamDiaryWidgetClass) {
		DreamDiaryWidgetRef = CreateWidget<UDreamDiaryWidget>(GetWorld(), DreamDiaryWidgetClass);
		if (DreamDiaryWidgetRef) {
			DreamDiaryWidgetRef->AddToViewport();
		}
	}

	if (Image_DreamDiary_Updated->GetVisibility() == ESlateVisibility::Visible) {
		Image_DreamDiary_Updated->SetVisibility(ESlateVisibility::Hidden);
		BattleManagerSystem->isDreamDiaryUpdated = false;
	}
}

void UHubworldHUDWidget::ClickSave()
{
	if (SaveExitAlertModalClass) {
		SaveExitAlertModalRef = CreateWidget<USaveExitAlertModalWidget>(GetWorld(), SaveExitAlertModalClass);
		if (SaveExitAlertModalRef) {
			SaveExitAlertModalRef->AddToViewport();

			FDateTime CurrentDateTime = FDateTime::Now();
			FString LastSaveTime = FString::Printf(TEXT("마지막 저장: %d년 %d월 %d일 %d시 %d분"), CurrentDateTime.GetYear(), CurrentDateTime.GetMonth(), CurrentDateTime.GetDay(), CurrentDateTime.GetHour(), CurrentDateTime.GetMinute());
			SaveExitAlertModalRef->TextBlock_Warning->SetText(FText::FromString(LastSaveTime));
		}
	}
	if (SaveExitAlertModalRef) {
		SaveExitAlertModalRef->Button_Yes->OnClicked.AddDynamic(this, &UHubworldHUDWidget::ClickSaveExitAlertModalYes);
		SaveExitAlertModalRef->Button_No->OnClicked.AddDynamic(this, &UHubworldHUDWidget::ClickSaveExitAlertModalNo);
	}
}

void UHubworldHUDWidget::ClickSaveExitAlertModalYes()
{
	KNOCKturneGameState->SaveKNOCKturneData();
	SaveExitAlertModalRef->RemoveFromParent();
}

void UHubworldHUDWidget::ClickSaveExitAlertModalNo()
{
	SaveExitAlertModalRef->RemoveFromParent();
}
