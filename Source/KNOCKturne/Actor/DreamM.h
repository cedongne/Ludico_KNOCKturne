// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NPC.h"

#include "DreamM.generated.h"

UCLASS()
class KNOCKTURNE_API ADreamM : public ANPC
{
	GENERATED_BODY()

public:
	ADreamM();

protected:
	virtual void BeginPlay() override;
};
