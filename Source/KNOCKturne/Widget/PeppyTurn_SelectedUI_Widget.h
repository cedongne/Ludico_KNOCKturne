// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "PeppyTurn_SelectedIcon_Widget.h"
#include "GameInstance/BattleManagerSystem.h"

#include "PeppyTurn_SelectedUI_Widget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurn_SelectedUI_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

	class UBattleManagerSystem* BattleManagerSystem;

protected:
	TArray<UUserWidget*> PeppyTurnWidgetArr;
	UTexture2D* cancelimg;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UPeppyTurn_SelectedIcon_Widget* BP_PeppyTurnIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_NumBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SkillError;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_SelectNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Cancel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* PeppyTurn_SkillError;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurnWidget* PeppyTurnWidget;

	UFUNCTION(BlueprintimplementableEvent)
	void PlaySkillErrorAnim();
	UFUNCTION()
	void CancelSkill(int cancelNum, USkillHoverWidget* SkillHover);
	UFUNCTION()
	void OnHovered_SelectedSkill();
	UFUNCTION()
	void OnClick_CancelSkill();
};
