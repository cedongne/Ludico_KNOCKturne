// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/PlayerController.h"

#include "KNOCKturneLevelScriptActor.h"

#include "PeppyController.generated.h"

UCLASS()
class KNOCKTURNE_API APeppyController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
public:
	APeppyController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanInteraction = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EInteractionType CurrentInteractionType;

	UFUNCTION(BlueprintCallable)
	void Interaction();
};
