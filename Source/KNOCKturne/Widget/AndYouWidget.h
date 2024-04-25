// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AndYouWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UAndYouWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();

	class UGameInstance* GameInstance;
	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;

	void SetBattleClearTime();
	void SetTryBattleCountText();
	void SetSelectedSkills();
	void SetPlayTime();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_BattleClearTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_PlayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_TryBattleCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SpecialSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Item;
};
