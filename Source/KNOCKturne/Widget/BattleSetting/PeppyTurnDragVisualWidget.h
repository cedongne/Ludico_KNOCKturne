// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PeppyTurnDragVisualWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurnDragVisualWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_DragVisual;
};
