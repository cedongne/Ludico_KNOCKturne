// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackageSelectedUIWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESelectedSkillType : uint8 {
	Skill	UMETA(DisplayName = "Skill"),
	SpecialSkill	UMETA(DisplayName = "SpecialSkill"),
	Item	UMETA(DisplayName = "Item")
};
UCLASS()
class KNOCKTURNE_API UPackageSelectedUIWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	class UBattleManagerSystem* BattleManagerSystem;

protected:
	TArray<UUserWidget*> PackageWidgetArr;
	UTexture2D* cancelimg;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SkillError;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Cancel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SkillError;

	ESelectedSkillType SelectedSkillType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PackageWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPackageWidget* PackageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillCardHoverWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SpecialSkillCardHoverWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemSkillCardHoverWidgetClass;

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySkillErrorAnim();
	UFUNCTION()
	void SetHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget);
	UFUNCTION()
	void ClickCancelBtn();
	UFUNCTION()
	void CancelSelectedSkill();
	UFUNCTION()
	void CancelSelectedItem();
	UFUNCTION()
	void HoverBackgroundBtn();
	UFUNCTION()
	void CreateSkillHoverWidget();
	UFUNCTION()
	void CreateSpecialSkillHoverWidget();
	UFUNCTION()
	void CreateItemHoverWidget();
};
