// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffIconFormWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UBuffIconFormWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

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
	class UProgressBar* ProgressBar_Term;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBuffHoverWidget* CurBuffHoverWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BuffHoverWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	bool IsPeppyBuff = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EBuffType CurBuffType;

	UFUNCTION(BlueprintCallable)
	FString GetSkillIndexByKeyword(EBuffType BuffType, FString Num);
	UFUNCTION(BlueprintCallable)
	FString RedefineDescription(int RowNum);

	UFUNCTION(BlueprintCallable)
	void CreateHoverWidget();
	UFUNCTION(BlueprintCallable)
	void SetHoverWidgetUI(UBuffHoverWidget* BuffHoverWidget);
	UFUNCTION(BlueprintCallable)
	void SetHoverWidgetPos(UBuffHoverWidget* BuffHoverWidget);
	UFUNCTION(BlueprintCallable)
	void  SetHoverBackgroundAngle(UBuffHoverWidget* BuffHoverWidget);
	UFUNCTION(BlueprintCallable)
	void SetProgressBarTerm();
};
