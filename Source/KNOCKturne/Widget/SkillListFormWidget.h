// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "SkillDescriptionComponent.h"
#include "SkillHoverWidget.h"
#include "PeppyTurnWidget.h"

#include "SkillListFormWidget.generated.h"

/**
 * 
 */

enum CurrentWidget {
	PakageSkillWidget,
	PeppyTurnUIWidget
};

UCLASS()
class KNOCKTURNE_API USkillListFormWidget : public UUserWidget
{
	GENERATED_BODY()
	USkillListFormWidget(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;
	class UBattleManagerSystem* BattleManagerSystem;

protected:
	TArray<UUserWidget*> PackageSkillWidgetArr;
	TArray<UUserWidget*> SkillHoverWidgetArr;
	TArray<UUserWidget*> PeppyTurnWidgetArr;
	UTexture2D* SelectedSkillImg;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_selected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox;

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
	class UTextBlock* TextBlock_CoolTimeSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Stance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PackageSkillWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPackageSkillWidget* PackageSkillWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurnWidget* PeppyTurnWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillHoverClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkillHoverWidget* SkillHoverWidgetRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkillDescriptionComponent* SkillDescriptionComponent;

	CurrentWidget curWidget;

	UFUNCTION()
	void SelectSkill(int clickedNum, USkillHoverWidget* SkillHover);
	UFUNCTION()
	void OnClick_Skill();
	UFUNCTION()
	void AddSkillInSelectedUI();
	UFUNCTION()
	void CreateHoverWidget(int hoveredNum, UButton* backgroundBtn, bool isSelectedUI);
	UFUNCTION()
	void OnHovered_Skill();
};
