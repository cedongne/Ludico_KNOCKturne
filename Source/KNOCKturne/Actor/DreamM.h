// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NPC.h"
#include "Peppy.h"
#include "Widget/DialogueWidget.h"
#include "Widget/InteractionPopupWidget.h"

#include "DreamM.generated.h"

UCLASS()
class KNOCKTURNE_API ADreamM : public ANPC
{
	GENERATED_BODY()
	class UBattleManagerSystem* BattleManagerSystem;
	TArray<UUserWidget*> AllEndingCreditWidgetArr;

public:
	ADreamM();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BeforeSelectingDialogue = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDialogueWidget* DialogueWidgetRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInteractionPopupWidget* InteractionUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_EndingCreditClass;

	UFUNCTION(BlueprintCallable)
	void SelectDialogue();
	UFUNCTION(BlueprintCallable)
	void DreamMStartTalk();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DreamMRandomTalk();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DreamMAfterBattleTalk();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DreamMDreamFragment();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetPeppyName();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DreamMEndCreditTalk();

protected:
	virtual void BeginPlay() override;

	APeppy* Peppy;
};
