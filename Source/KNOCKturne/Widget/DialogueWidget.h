// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Component/DialogueTableComponent.h"

#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GetNextDialogueLine(UDialogueTableComponent* DialogueTableComponent);
};
