// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"

#include "KNOCKturneLevelScriptActor.h"
#include "GameMode/KNOCKturneGameState.h"
#include "GameMode/PeppyController.h"
#include "Widget/DialogueWidget.h"
#include "Widget/HubworldHUDWidget.h"
#include "Actor/Peppy.h"

#include "HubWorldLevelScriptActor.generated.h"

/**
 * 
 */
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
	bool isPrologue = false;
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

protected:
	virtual void BeginPlay() override;

	APeppyController* PeppyController;
	APeppy* Peppy;
	TSubclassOf<UUserWidget> DialogueWidgetClass;
	class UDialogueWidget* DialogueWidgetRef;
	TSubclassOf<UUserWidget> HubworldHUDClass;
	class UHubworldHUDWidget* HubworldHUDRef;

	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BlackScreenOn();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BlackScreenOff();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void MoveDirection();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void StartPrologueDialogue();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	bool MoveDirectionTF(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void StorePrevCameraRotation();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void StorePrevCameraLocation();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void StorePrevCameraTransform();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void PrologueDirection(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void CallMoveDirection(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void NextIsDirection(FDialogueData DataTable);
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void AfterPrologueDirection();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void SetPeppyHiddenOrNot();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void BattleFailDialogueAllEnded();
	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
	void CreateHubworldHUD();
};
