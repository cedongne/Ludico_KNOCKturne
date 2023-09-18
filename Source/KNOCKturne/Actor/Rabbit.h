// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NPC.h"
#include "Peppy.h"

#include "Rabbit.generated.h"

UCLASS()
class KNOCKTURNE_API ARabbit : public ANPC
{
	GENERATED_BODY()

public:
	ARabbit();

protected:
	virtual void BeginPlay() override;

	APeppy* Peppy;

public:	
	UFUNCTION(BlueprintCallable)
	void RabbitStartTalk();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RabbitRandomTalk();

};
