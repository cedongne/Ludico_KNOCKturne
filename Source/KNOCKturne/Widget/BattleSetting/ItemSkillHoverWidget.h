// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BattleSetting/CommonSkillHoverWidget.h"
#include "ItemSkillHoverWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UItemSkillHoverWidget : public UCommonSkillHoverWidget
{
	GENERATED_BODY()
	AKNOCKturneGameState* KNOCKturneGameState;
protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Count;

	void SetHoverWidgetUI(int RowNum, bool IsSelected) override;
	FString CheckValueN(int SkillIndex, float ValueN) override;
	FString CheckValueM(int SkillIndex, float ValueM) override;
	FString GetSkillIndexByKeyword(int RowNum, FString Num) override;
	FString RedefineDescription(int RowNum) override;
	void ClickButton() override;
};
