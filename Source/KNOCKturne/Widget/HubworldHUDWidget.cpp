// Fill out your copyright notice in the Description page of Project Settings.


#include "HubworldHUDWidget.h"
#include "GameInstance/KNOCKturneGameInstance.h"

UHubworldHUDWidget::UHubworldHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

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
	if (Button_Diary) {
		Button_Diary->OnClicked.AddDynamic(this, &UHubworldHUDWidget::OnClick_ButtonDiary);
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
		KNOCKturneGameState->isDreamDiaryUpdated = false;
	}
}