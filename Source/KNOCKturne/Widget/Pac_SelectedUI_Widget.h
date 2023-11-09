// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"

#include "Pac_SelectedUI_Widget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPac_SelectedUI_Widget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();

	class UBattleManagerSystem* BattleManagerSystem;

protected:
	TArray<UUserWidget*> PackageSkillWidgetArr;
	UTexture2D* cancelimg;

public:
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PackageSkillWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPackageSkillWidget* PackageSkillWidget;


	UFUNCTION()
	void OnClick_Cancel();
	UFUNCTION()
	void CancelSkill(int cancelNum, USkillHoverWidget* SkillHover);
	UFUNCTION()
	void OnClick_CancelSkill();
	UFUNCTION()
	void CancelSpecialty(USpecialtyHoverWidget* SpecialtyHover);
	UFUNCTION()
	void CancelItem(UItemHoverWidget* ItemHover);
};
