// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/Button.h"
#include "Components/RichTextBlock.h"

#include "ItemCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UItemCardWidget : public UUserWidget
{
	GENERATED_BODY()

	void NativePreConstruct();
	void NativeConstruct();

protected:
	TArray<UUserWidget*> DreamFragmentWidgetArr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_DreamFragments_SubBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_DreamFragments_SubBackground_Selected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SubBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URichTextBlock* RichTextBlock_Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Easteregg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URichTextBlock* RichTextBlock_EastereggCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Background;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemCardFormClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DreamFragmentWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDreamFragmentWidget* DreamFragmentWidget;

	UFUNCTION(BlueprintCallable)
	void Button_BackgroundOnClicked();
};
