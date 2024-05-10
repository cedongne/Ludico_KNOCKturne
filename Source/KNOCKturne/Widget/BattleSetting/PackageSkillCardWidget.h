// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonSkillCardWidget.h"
#include "PackageSkillCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPackageSkillCardWidget : public UCommonSkillCardWidget
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
	class UTextBlock* TextBlock_CoolTimeSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Stance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillCardHoverWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PackageWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPackageWidget* PackageWidget;
};
