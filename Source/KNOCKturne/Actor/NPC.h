// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetComponent.h"
#include "NPC.generated.h"

UCLASS()
class KNOCKTURNE_API ANPC : public APawn
{
	GENERATED_BODY()

public:
	ANPC();

protected:
	virtual void BeginPlay() override;

public:	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsHoverMouse;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool GiveFragment = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TalkCount = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCanInteraction();
	virtual void SetCanInteraction_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCannotInteraction();
	virtual void SetCannotInteraction_Implementation();
};
