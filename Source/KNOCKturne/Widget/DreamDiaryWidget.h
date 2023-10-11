// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "GameMode/KNOCKturneGameState.h"
#include "Component/DialogueTableComponent.h"

#include "DreamDiaryWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UDreamDiaryWidget : public UUserWidget
{
	GENERATED_BODY()

	UDreamDiaryWidget(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct();
	virtual void NativeConstruct();

	AKNOCKturneGameState* KNOCKturneGameState;

protected:

	class UDataTable* DreamDiaryTable;
	class UDataTable* StringTable;
	TArray<FDreamDiaryData*> DreamDiaryRows;
	class UDialogueTableComponent* DialogueTableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_DreamCatcher;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Dreamcatcher;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Point_7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Unpopened_Even;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Unpopened_Odd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URichTextBlock* RichTextBlock_Content_Even;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URichTextBlock* RichTextBlock_Content_Odd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_RoundAlert_Odd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_NotYet_Odd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_RoundAlert_Even;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_NotYet_Even;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Lines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_EpisodeNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_EpisodeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Exit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Next;

	UFUNCTION()
	void Button_ExitOnClicked();
	UFUNCTION()
	void Button_BackOnClicked();
	UFUNCTION()
	void Button_NextOnClicked();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_diary_point_1_v2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_diary_point_2_v2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_diary_dreamcatcher_v2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentOddPage = -1;

	UFUNCTION(BlueprintCallable)
	UDataTable* GetStringTable();
	UFUNCTION(BlueprintCallable)
	void Unopened_Odd();
	UFUNCTION(BlueprintCallable)
	void Unopened_Even();
	UFUNCTION(BlueprintCallable)
	void SetWhetherToOpenDreamDiaryOrNot(bool isNextButton);
	UFUNCTION(BlueprintCallable)
	void SetDreamDiaryContent(bool isOddOpen, bool isEvenOpen);
	UFUNCTION(BlueprintCallable)
	void SetCurrentOddPageToNextPage();
	UFUNCTION(BlueprintCallable)
	void SetCurrentOddPageToBackPage();
	UFUNCTION(BlueprintCallable)
	void DefaultSetting();
	UFUNCTION(BlueprintCallable)
	void SetDreamcatcherPointUI(int32 PointNum);
};
