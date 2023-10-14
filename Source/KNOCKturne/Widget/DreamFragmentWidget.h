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
#include "SkillDescriptionComponent.h"
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
	int32 SelectedItemNum;

protected:
	class UDataTable* ItemTable;
	TArray<FItemData*> ItemTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;
	TArray<int32> RndItemRowNumArr;
	USkillDescriptionComponent* SkillDescriptionComponent;
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
	void AlertModal_YesOnClicked();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CallDreamFragmentTalk();
};
