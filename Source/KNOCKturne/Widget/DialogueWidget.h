// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "string"

#include "Component/DialogueTableComponent.h"

#include "DialogueWidget.generated.h"

/**
 * 
 */


UCLASS()
class KNOCKTURNE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

	void NativePreConstruct();

protected:
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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GetNextDialogueLine(UDialogueTableComponent* DialogueTableComponent);

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
};
