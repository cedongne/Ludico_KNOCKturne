// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"
#include "CommonSkillHoverWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UCommonSkillHoverWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

	class UGameInstance* GameInstance;
	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_selected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_CheckBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_IconBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URichTextBlock* TextBlock_Description;

	UFUNCTION()
	virtual void SetHoverWidgetUI(int RowNum, bool IsSelected);
	UFUNCTION()
	virtual FString CheckValueN(int SkillIndex, float ValueN);
	UFUNCTION()
	virtual FString CheckValueM(int SkillIndex, float ValueM);
	UFUNCTION()
	virtual FString GetSkillIndexByKeyword(int RowNum, FString Num);
	UFUNCTION()
	virtual FString RedefineDescription(int RowNum);

	UFUNCTION()
	FString CheckProbability(float Probability);
	UFUNCTION()
	void Remove();
	UFUNCTION()
	void SetCheckBox();
};
