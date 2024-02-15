// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Component/DialogueTableComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "GameMode/KNOCKturneGameState.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "ItemCardWidget.h"
#include "AlertModalWidget.h"
#include "DialogueWidget.h"
#include "DreamFragmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UDreamFragmentWidget : public UUserWidget
{
	GENERATED_BODY()

	UDreamFragmentWidget(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct();
	void NativeConstruct();

	AKNOCKturneGameState* KNOCKturneGameState;
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	int32 SelectedItemNum;

protected:
	TArray<int32> RndItemRowNumArr;
	TArray<UUserWidget*> DialogueWidgetArr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Cancel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Select;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UGridPanel* GridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemCardFormClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemCardWidget* ItemCardFormRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> AlertModalClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAlertModalWidget* AlertModalRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UItemCardWidget*> ItemCardArr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UFUNCTION(Blueprintcallable)
	void PickRandomItem();
	UFUNCTION(Blueprintcallable)
	void SetItemCardUI();
	UFUNCTION(BlueprintCallable)
	void Button_SelectOnClicked();
	UFUNCTION(BlueprintCallable)
	void OnClicked_AlertModal_Yes();
	UFUNCTION(BlueprintCallable)
	void OnClicked_AlertModal_No();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CallDreamFragmentTalk();

	// 사운드
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NoticeSound();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SelectSound();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CancelSound();

	// 아이템 설명 재정의
	FString CheckValueN(int SkillIndex, float ValueN);
	FString CheckValueM(int SkillIndex, float ValueM);
	FString GetSkillIndexByKeyword(int RowNum, FString Num);
	FString RedefineDescription(int RowNum);
};
