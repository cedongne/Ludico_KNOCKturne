// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/PlayerController.h"

#include "LevelScriptActor/KNOCKturneLevelScriptActor.h"

#include "PeppyController.generated.h"

UCLASS()
class KNOCKTURNE_API APeppyController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AKNOCKturneLevelScriptActor* CurrentLevelScriptActor;

public:
	APeppyController();

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UDialogueTableComponent* PrologueDialogueComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanInteraction = false;

	void Interaction();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Interaction();
};
