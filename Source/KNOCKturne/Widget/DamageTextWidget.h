// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* DamageTextUp;

	UFUNCTION(BlueprintCallable)
	void PlayDamgeTextUpAnim();
};
