// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "PackageSkillWidget.h"
#include "Pac_SelectedUI_Widget.h"
#include "GameMode/KNOCKturneGameState.h"
#include "SkillDescriptionComponent.h"
#include "ItemHoverWidget.h"

#include "ItemListFormWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UItemListFormWidget : public UUserWidget
{
	GENERATED_BODY()
	UItemListFormWidget(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct();
	void NativeConstruct();

	AKNOCKturneGameState* KNOCKturneGameState;

protected:
	TArray<UUserWidget*> PackageSkillWidgetArr;
	USkillDescriptionComponent* SkillDescriptionComponent;

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
	class UTextBlock* TextBlock_SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Count;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PackageSkillWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPackageSkillWidget* PackageSkillWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemHoverClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemHoverWidget* ItemHoverWidgetRef;

	int hoveredNum = 0;

	UFUNCTION()
	void SelectItem(int clickedNum);
	UFUNCTION()
	void OnClick_Item();
	UFUNCTION()
	void OnHovered_Item();
};
