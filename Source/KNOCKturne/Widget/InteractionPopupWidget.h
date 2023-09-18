// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPopupWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UInteractionPopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativePreConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_interaction;
};
