// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UItemIconWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Icon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UHUDItemHoverWidget* HUDItemHoverWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> HUDItemHoverWidgetClass;

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
	void SetHoverWidgetUI(UHUDItemHoverWidget* HoverWidget);
	UFUNCTION(BlueprintCallable)
	void SetHoverWidgetPos(UHUDItemHoverWidget* HoverWidget);
};
