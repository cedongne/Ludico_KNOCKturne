// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PeppyTurn_SelectedIcon_Widget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurn_SelectedIcon_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SelectedSkillIcon;
};
