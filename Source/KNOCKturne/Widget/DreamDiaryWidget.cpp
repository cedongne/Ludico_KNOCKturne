// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamDiaryWidget.h"

#include "GameInstance/KNOCKturneGameInstance.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "Component/DialogueTableComponent.h"

#include <string>

UDreamDiaryWidget::UDreamDiaryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	FString DreamDiaryDataPath = TEXT("/Game/Assets/DataTable/DreamDiaryTable.DreamDiaryTable");
	FString StringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STRINGTABLE(*StringTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DREAMDIARYTABLE(*DreamDiaryDataPath);
	DreamDiaryTable = DT_DREAMDIARYTABLE.Object;
	StringTable = DT_STRINGTABLE.Object;
}

void UDreamDiaryWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	CanvasPanel_DreamCatcher = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel_DreamCatcher"));
	Image_Dreamcatcher = (UImage*)GetWidgetFromName(TEXT("Image_Dreamcatcher"));
	Image_Point = (UImage*)GetWidgetFromName(TEXT("Image_Point"));
	Image_Point_1 = (UImage*)GetWidgetFromName(TEXT("Image_Point_1"));
	Image_Point_2 = (UImage*)GetWidgetFromName(TEXT("Image_Point_2"));
	Image_Point_3 = (UImage*)GetWidgetFromName(TEXT("Image_Point_3"));
	Image_Point_4 = (UImage*)GetWidgetFromName(TEXT("Image_Point_4"));
	Image_Point_5 = (UImage*)GetWidgetFromName(TEXT("Image_Point_5"));
	Image_Point_6 = (UImage*)GetWidgetFromName(TEXT("Image_Point_6"));
	Image_Point_7 = (UImage*)GetWidgetFromName(TEXT("Image_Point_7"));
	Image_Unpopened_Even = (UImage*)GetWidgetFromName(TEXT("Image_Unpopened_Even"));
	Image_Unpopened_Odd = (UImage*)GetWidgetFromName(TEXT("Image_Unpopened_Odd"));
	RichTextBlock_Content_Even = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_Content_Even"));
	RichTextBlock_Content_Odd = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_Content_Odd"));
	Image_RoundAlert_Odd = (UImage*)GetWidgetFromName(TEXT("Image_RoundAlert_Odd"));
	TextBlock_NotYet_Odd = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_NotYet_Odd"));
	Image_RoundAlert_Even = (UImage*)GetWidgetFromName(TEXT("Image_RoundAlert_Even"));
	TextBlock_NotYet_Even = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_NotYet_Even"));
	Image_Lines = (UImage*)GetWidgetFromName(TEXT("Image_Lines"));
	TextBlock_EpisodeNum = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EpisodeNum"));
	TextBlock_EpisodeName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EpisodeName"));
	Button_Exit = (UButton*)GetWidgetFromName(TEXT("Button_Exit"));
	Button_Back = (UButton*)GetWidgetFromName(TEXT("Button_Back"));
	Button_Next = (UButton*)GetWidgetFromName(TEXT("Button_Next"));
}

void UDreamDiaryWidget::NativeConstruct() {
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	DreamDiaryTable->GetAllRows<FDreamDiaryData>("GetAllRows", DreamDiaryRows);

	DefaultSetting();

	if (Button_Exit) {
		Button_Exit->OnClicked.AddDynamic(this, &UDreamDiaryWidget::Button_ExitOnClicked);
	}
	if (Button_Back) {
		Button_Back->OnClicked.AddDynamic(this, &UDreamDiaryWidget::Button_BackOnClicked);
	}
	if (Button_Next) {
		Button_Next->OnClicked.AddDynamic(this, &UDreamDiaryWidget::Button_NextOnClicked);
	}
}

UDataTable* UDreamDiaryWidget::GetStringTable() {
	return StringTable;
}

void UDreamDiaryWidget::Unopened_Odd() {
	CanvasPanel_DreamCatcher->SetVisibility(ESlateVisibility::Hidden);
	TextBlock_EpisodeNum->SetVisibility(ESlateVisibility::Hidden);
	TextBlock_EpisodeName->SetVisibility(ESlateVisibility::Hidden);
	RichTextBlock_Content_Odd->SetVisibility(ESlateVisibility::Hidden);
	Image_Unpopened_Odd->SetVisibility(ESlateVisibility::Visible);
	Image_RoundAlert_Odd->SetVisibility(ESlateVisibility::Visible);
	TextBlock_NotYet_Odd->SetVisibility(ESlateVisibility::Visible);
}

void UDreamDiaryWidget::Unopened_Even() {
	RichTextBlock_Content_Even->SetVisibility(ESlateVisibility::Hidden);

	if (CurrentOddPage + 1 > DreamDiaryRows.Num() - 1) {
		Image_Unpopened_Even->SetVisibility(ESlateVisibility::Hidden);
		Image_RoundAlert_Even->SetVisibility(ESlateVisibility::Hidden);
		TextBlock_NotYet_Even->SetVisibility(ESlateVisibility::Hidden);
		Image_Lines->SetVisibility(ESlateVisibility::Visible);
		Button_Next->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		Image_Unpopened_Even->SetVisibility(ESlateVisibility::Visible);
		Image_RoundAlert_Even->SetVisibility(ESlateVisibility::Visible);
		TextBlock_NotYet_Even->SetVisibility(ESlateVisibility::Visible);
	}
}

void UDreamDiaryWidget::SetWhetherToOpenDreamDiaryOrNot(bool isNextButton) {
	if (isNextButton) {
		if (Button_Back->GetVisibility() == ESlateVisibility::Hidden) {
			Button_Back->SetVisibility(ESlateVisibility::Visible);
		}

		if (KNOCKturneGameState->DreamDiaryOpenRow >= CurrentOddPage + 3) { // 다음 장 오른쪽 페이지 해금 여부
			SetCurrentOddPageToNextPage();
			SetDreamDiaryContent(true, true);
		}
		else {
			if (KNOCKturneGameState->DreamDiaryOpenRow >= CurrentOddPage + 2) { // 다음 장 왼쪽 페이지 해금 여부
				SetCurrentOddPageToNextPage();
				SetDreamDiaryContent(true, false);
			}
			else {
				SetCurrentOddPageToNextPage();
				Unopened_Odd();
			}
			Unopened_Even();
		}
	}
	else {
		if (KNOCKturneGameState->DreamDiaryOpenRow >= CurrentOddPage - 1) { // 이전 장 오른쪽 페이지 해금 여부
			SetCurrentOddPageToBackPage();
			SetDreamDiaryContent(true, true);
		}
		else {
			if (KNOCKturneGameState->DreamDiaryOpenRow >= CurrentOddPage - 2) { // 이전 장 왼족 페이지 해금 여부
				SetCurrentOddPageToBackPage();
				SetDreamDiaryContent(true, false);
			}
			else {
				SetCurrentOddPageToBackPage();
				Unopened_Odd();
			}
			Unopened_Even();
		}
	}
}

void UDreamDiaryWidget::SetDreamDiaryContent(bool isOddOpen, bool isEvenOpen) {
	if (isOddOpen) {
		Image_Unpopened_Odd->SetVisibility(ESlateVisibility::Hidden);
		Image_RoundAlert_Odd->SetVisibility(ESlateVisibility::Hidden);
		TextBlock_NotYet_Odd->SetVisibility(ESlateVisibility::Hidden);
		RichTextBlock_Content_Odd->SetVisibility(ESlateVisibility::Visible);

		if (CurrentOddPage != -1) {
			FString DreamDiaryCurrentOddtPageString = GetStringTable()->FindRow<FDialogueString>(FName(DreamDiaryRows[CurrentOddPage]->DreamDiaryStringID), TEXT(""))->KOR;
			RichTextBlock_Content_Odd->SetText(FText::FromString(DreamDiaryCurrentOddtPageString));
		}
		else {
			CanvasPanel_DreamCatcher->SetVisibility(ESlateVisibility::Visible);
			TextBlock_EpisodeNum->SetVisibility(ESlateVisibility::Visible);
			TextBlock_EpisodeName->SetVisibility(ESlateVisibility::Visible);
			Button_Back->SetVisibility(ESlateVisibility::Hidden);
			RichTextBlock_Content_Odd->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (isEvenOpen) {
		Image_Unpopened_Even->SetVisibility(ESlateVisibility::Hidden);
		Image_RoundAlert_Even->SetVisibility(ESlateVisibility::Hidden);
		TextBlock_NotYet_Even->SetVisibility(ESlateVisibility::Hidden);
		RichTextBlock_Content_Even ->SetVisibility(ESlateVisibility::Visible);

		FString DreamDiaryCurrentOddtPageString = GetStringTable()->FindRow<FDialogueString>(FName(DreamDiaryRows[CurrentOddPage + 1]->DreamDiaryStringID), TEXT(""))->KOR;
		RichTextBlock_Content_Even->SetText(FText::FromString(DreamDiaryCurrentOddtPageString));
	}
}

void UDreamDiaryWidget::SetCurrentOddPageToNextPage() {
	if (CanvasPanel_DreamCatcher->GetVisibility() == ESlateVisibility::Visible) {
		CanvasPanel_DreamCatcher->SetVisibility(ESlateVisibility::Hidden);
		TextBlock_EpisodeNum->SetVisibility(ESlateVisibility::Hidden);
		TextBlock_EpisodeName->SetVisibility(ESlateVisibility::Hidden);
	}
	CurrentOddPage += 2;
}

void UDreamDiaryWidget::SetCurrentOddPageToBackPage() {
	if (Image_Lines->GetVisibility() == ESlateVisibility::Visible) {
		Image_Lines->SetVisibility(ESlateVisibility::Hidden);
		Button_Next->SetVisibility(ESlateVisibility::Visible);
	}
	CurrentOddPage -= 2;
}

void UDreamDiaryWidget::DefaultSetting() {
	FString DreamDiaryFirstPageString = GetStringTable()->FindRow<FDialogueString>(FName(DreamDiaryRows[0]->DreamDiaryStringID), TEXT(""))->KOR;
	RichTextBlock_Content_Even->SetText(FText::FromString(DreamDiaryFirstPageString));

	for (int index = 0; index < KNOCKturneGameState->DreamDiaryOpenRow; index++) {
		SetDreamcatcherPointUI(index);
	}

	if (KNOCKturneGameState->DreamDiaryOpenRow > DreamDiaryRows.Num() - 1) {
		KNOCKturneGameState->DreamDiaryOpenRow = 3;
	}
}

void UDreamDiaryWidget::SetDreamcatcherPointUI(int32 PointNum) {
	switch (PointNum) {
	case 0:
	{
		Image_Point->SetBrushFromTexture(UI_diary_point_1_v2);
		Image_Point_1->SetBrushFromTexture(UI_diary_point_2_v2);
	}
	case 1:
	{
		Image_Point_2->SetBrushFromTexture(UI_diary_point_1_v2);
		Image_Point_3->SetBrushFromTexture(UI_diary_point_2_v2);
	}
	case 2:
	{
		Image_Point_4->SetBrushFromTexture(UI_diary_point_1_v2);
		Image_Point_5->SetBrushFromTexture(UI_diary_point_2_v2);
	}
	case 3:
	{
		Image_Point_6->SetBrushFromTexture(UI_diary_point_1_v2);
		Image_Point_7->SetBrushFromTexture(UI_diary_point_2_v2);
		Image_Dreamcatcher->SetBrushFromTexture(UI_diary_dreamcatcher_v2);
	}

	}
}

void UDreamDiaryWidget::Button_ExitOnClicked() {
	this->RemoveFromParent();
}

void UDreamDiaryWidget::Button_BackOnClicked() {
	SetWhetherToOpenDreamDiaryOrNot(false);
}

void UDreamDiaryWidget::Button_NextOnClicked() {
	SetWhetherToOpenDreamDiaryOrNot(true);
}