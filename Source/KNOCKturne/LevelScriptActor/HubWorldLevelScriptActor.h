// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"

#include "Actor/DreamM.h"
#include "Actor/Rabbit.h"
#include "Actor/Lake.h"
#include "KNOCKturneLevelScriptActor.h"
#include "GameMode/KNOCKturneGameState.h"
#include "GameMode/PeppyController.h"
#include "Widget/DialogueWidget.h"
#include "Widget/HubworldHUDWidget.h"
#include "Widget/LoadingWidget.h"

#include "HubWorldLevelScriptActor.generated.h"

UCLASS()
class KNOCKTURNE_API AHubWorldLevelScriptActor : public AKNOCKturneLevelScriptActor
{
	GENERATED_BODY()

	AKNOCKturneGameState* KNOCKturneGameState;

	
public:
	AHubWorldLevelScriptActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UDialogueTableComponent* PrologueDialogueComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MDSelection = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPrologue = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSkip = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PrevCameraRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PrevCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PrevPeppyRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PrevPeppyLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform OriginalRabbitTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PrevRabbitRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform OriginalPeppyTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform OriginalCameraTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PrevDreamMRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalDreamMLocation;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> HubworldActors;
	UPROPERTY(EditAnywhere)
	ADreamM* DreamMActor;
	UPROPERTY(EditAnywhere)
	ARabbit* RabbitActor;
	UPROPERTY(EditAnywhere)
	ALake* LakeActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDialogueWidget* DialogueWidgetRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> HubworldHUDClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UHubworldHUDWidget* HubworldHUDRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_EscClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* BP_EscRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_BlackClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* BP_BlackRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> LoadingWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ULoadingWidget* LoadingWidgetRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_BlinkClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* BP_BlinkRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_DreamFragmentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* BP_DreamFragmentRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelSequence* FadeIn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelSequence* Hubworld_Cabin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULevelSequencePlayer* LevelSequencePlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALevelSequenceActor* SequenceActor;

	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BlackScreenOn();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BlackScreenOff();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void MoveDirection();
	UFUNCTION(Blueprintcallable)
	void StartPrologueDialogue();
	UFUNCTION(Blueprintcallable)
	bool MoveDirectionTF(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable)
	void StorePrevCameraRotation();
	UFUNCTION(Blueprintcallable)
	void StorePrevCameraLocation();
	UFUNCTION(Blueprintcallable)
	void StorePrevCameraTransform();
	UFUNCTION(Blueprintcallable)
	void PrologueDirection(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable)
	void CallMoveDirection(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable)
	void NextIsDirection(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable)
	void AfterPrologueDirection();
	UFUNCTION(Blueprintcallable)
	void SetPeppyHiddenOrNot();
	UFUNCTION(Blueprintcallable)
	void BattleFailDialogueAllEnded();
	UFUNCTION(Blueprintcallable)
	void CreateHubworldHUD();
	UFUNCTION(Blueprintcallable)
	void PrologueEnded();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void IfPrologueDirectionTrue();
	UFUNCTION(Blueprintcallable)
	void DefaultLocation();
	UFUNCTION(Blueprintcallable)
	void EscKeyEvent();
	UFUNCTION(Blueprintcallable)
	void StartLevelByCondition();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void Delay(float Duration);
	UFUNCTION(Blueprintcallable)
	void BattleFailDialogue();
	UFUNCTION(Blueprintcallable)
	void AfterBattleFailDirection(FDialogueData DialogueData);
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BindNpcTalk();
	UFUNCTION(Blueprintcallable)
	void RandomTalk();
	UFUNCTION(Blueprintcallable)
	void AfterBattleFailHubworldDialogueEnded();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BattleFailDialogueWithEventBinding();
	UFUNCTION(Blueprintcallable)
	void TalkWithNpcEnded();
	UFUNCTION(Blueprintcallable)
	void StartDreamFragmentDialogue();
	UFUNCTION(Blueprintcallable)
	void DreamMDirectionTrue();
	UFUNCTION(Blueprintcallable)
	void StartAfterBattleDialogue();
	UFUNCTION(Blueprintcallable)
	void AfterBattleDialogueEnded();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void SetState(FName StateGroup, FName State);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	class APeppy* Peppy;
	APeppyController* PeppyController;
};
