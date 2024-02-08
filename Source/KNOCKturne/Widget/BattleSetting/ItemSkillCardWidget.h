// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BattleSetting/CommonSkillCardWidget.h"
#include "ItemSkillCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UItemSkillCardWidget : public UCommonSkillCardWidget
{
	GENERATED_BODY()

protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	int32 GetCardSkillRowNum() override;
	UFUNCTION(BlueprintCallable)
	void CreateSkillHoverWidget() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Count;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemSkillCardHoverWidgetClass;
};
