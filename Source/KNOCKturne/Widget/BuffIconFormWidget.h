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

	UFUNCTION(BlueprintCallable)
	FString GetSkillIndexByKeyword(EBuffType BuffType, FString Num);
	UFUNCTION(BlueprintCallable)
	FString RedefineDescription(int RowNum);
};
