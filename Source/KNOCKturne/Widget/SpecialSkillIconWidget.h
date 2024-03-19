// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialSkillIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API USpecialSkillIconWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UActorManagerSystem* ActorManagerSystem;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Active;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Opacity60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_SpecialtyKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UHUDSpecialSkillHoverWidget* HUDSpecialSkillHoverWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> HUDSpecialSkillHoverWidgetClass;

	UFUNCTION()
	FString CheckProbability(float Probability);
	UFUNCTION()
	FString CheckValueN(int SkillIndex, float ValueN);
	UFUNCTION()
	FString CheckValueM(int SkillIndex, float ValueM);
	UFUNCTION()
	FString GetSkillIndexByKeyword(int RowNum, FString Num);
	UFUNCTION(BlueprintCallable)
	FString RedefineDescription(int RowNum);

	UFUNCTION(BlueprintCallable)
	void CreateHoverWidget();
	UFUNCTION(BlueprintCallable)
	void SetHoverWidgetUI(UHUDSpecialSkillHoverWidget* HoverWidget);
	UFUNCTION(BlueprintCallable)
	void SetHoverWidgetPos(UHUDSpecialSkillHoverWidget* HoverWidget);

	UFUNCTION(BlueprintCallable)
	void SetCoolTimeText();
};
