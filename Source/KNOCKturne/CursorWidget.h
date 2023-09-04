// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CursorWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UCursorWidget : public UUserWidget
{
	GENERATED_BODY()

	APlayerController* PlayerController;

	virtual void Construct();
	virtual void Tick(float DeltaTime);
};
