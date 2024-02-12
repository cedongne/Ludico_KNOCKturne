// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonSkillHoverWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "PackageSkillHoverWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPackageSkillHoverWidget : public UCommonSkillHoverWidget
{
	GENERATED_BODY()
protected:
	void NativePreConstruct() override;
	void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_CoolTimeSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Stance;

	void SetHoverWidgetUI(int RowNum, bool IsSelected) override;
	FString CheckValueN(int SkillIndex, float ValueN) override;
	FString CheckValueM(int SkillIndex, float ValueM) override;
	FString GetSkillIndexByKeyword(int RowNum, FString Num) override;
	FString RedefineDescription(int RowNum) override;
	void ClickButton() override;
};
