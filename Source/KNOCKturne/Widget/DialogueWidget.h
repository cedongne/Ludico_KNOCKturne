// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Engine/DataTable.h"
#include "string"

#include "GameInstance/BattleManagerSystem.h"
#include "Component/DialogueTableComponent.h"
#include "GameMode/PeppyController.h"
#include "GameMode/KNOCKturneGameState.h"

#include "DialogueWidget.generated.h"

/**
 * 
 */


UCLASS()
class KNOCKTURNE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

	void BeginPlay();
	void NativePreConstruct();

	AKNOCKturneGameState* KNOCKturneGameState;

protected:
	APeppyController* PeppyController;
	class UBattleManagerSystem* BattleManagerSystem;

	FString FullDialogue;
	TArray<int32> OpenBracesArray;
	int32 SkillIndexValueArrayIndex = -1;
	int32 CloseBracesIndex = 0;
	FString RedefinedDescription;
	bool InputEDuringWriting = false;
	bool isCameraMoving = false;
	bool isDirection = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_BlackScreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* HandCutScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_Peppy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_Npc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_CutScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_Dialogue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class URichTextBlock* RichTextBlock_Dialogue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_Continue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TextBlock_E;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_NpcName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Text_NpcName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_PeppyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Text_PeppyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_Dialogue_Select_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_Dialogue_Select_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TextBlock_Dialogue_Select_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TextBlock_Dialogue_Select_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UOverlay* Overlay_NpcName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UOverlay* Overlay_PeppyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* PeppyAppear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* DreamMAppear;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_peppy_basic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_peppy_shock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_peppy_noidea;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_dreamM_basic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_dreamM_shock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_dreamM_worry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_dreamM_happy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_dreamM_sadsmile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_dia_yellowrose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_hand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_lake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dream1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dream2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dream3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dreamW1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dreamW2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dreamW3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dreamW4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Im_cutS_pro_dreamW5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* icon_dia_select_yes_32_32;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* icon_dia_select_no_32_32;

	UPROPERTY(BlueprintReadWrite)
		float TextSpeed = 0.07;
	UPROPERTY(BlueprintReadWrite)
		int32 TypingIndex = 0;

	UFUNCTION(BlueprintCallable)
	void ChangeName(FDialogueData DataRow);
	UFUNCTION(BlueprintCallable)
		void ChangePeppyImg(FDialogueData DataRow);
	UFUNCTION(BlueprintCallable)
		void ChangeNPCImg(FDialogueData DataRow);
	UFUNCTION(BlueprintCallable)
		void ChangeBySpeakType(FDialogueData DataRow);
	UFUNCTION(BlueprintCallable)
		void ChangeCutScene(FDialogueData DataRow);
	UFUNCTION(BlueprintCallable)
		void ChangeDialogueUI(FDialogueData DataRow);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GetNextDialogueLine(UDialogueTableComponent* DialogueTableComponent);
	UFUNCTION(BlueprintCallable)
		FString GetCompleteRichTextTag(FString Dialogue);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void TypingEffect();
	UFUNCTION(BlueprintCallable)
		void DownArrowEvent();
	UFUNCTION(BlueprintCallable)
		void UpArrowEvent();
	UFUNCTION(BlueprintCallable)
		FString GetSkillIndexByKeyword(FString Num);
	UFUNCTION(BlueprintCallable)
		FString GetValueOfSkillIndex(FString Description, int32 OpenBracesArrayIndex);
	UFUNCTION(BlueprintCallable)
		FString RedefineLine(FString Description);
	UFUNCTION(BlueprintCallable)
		FString ApplyRedefinedLine(FString OriginalStr, UDialogueTableComponent* DialogueTableComponentRowVar);
	UFUNCTION(BlueprintCallable)
		void NextTalk(UDialogueTableComponent* DialogueTableComponentRowVar);
	UFUNCTION(BlueprintCallable)
		void InputEDuringTalking(UDialogueTableComponent* DialogueTableComponentRowVar);
	UFUNCTION(BlueprintCallable)
		void AfterBattleFailDirection(FDialogueData DataRow, UDialogueTableComponent* DialogueTableComponentVar);

	UFUNCTION(BlueprintCallable)
		void IsEndedDialogueRowsTrue();
	UFUNCTION(BlueprintCallable)
		void IsDirectionTrue();
};