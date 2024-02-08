// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "GameInstance/BattleManagerSystem.h"
#include "CommonSkillCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UCommonSkillCardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

	UGameInstance* GameInstance;
	class UBattleManagerSystem* BattleManagerSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_selected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_numbering;

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

	virtual int32 GetCardSkillRowNum();
	virtual void CreateSkillHoverWidget();
	UFUNCTION(BlueprintCallable)
	void SetHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget);
};
