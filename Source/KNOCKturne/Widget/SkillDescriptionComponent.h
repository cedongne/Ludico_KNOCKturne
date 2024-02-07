// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "Components/Button.h"
#include <Component/SpecialSkillComponent.h>
#include "Components/CanvasPanel.h"

#include "SkillDescriptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API USkillDescriptionComponent : public UActorComponent
{
	GENERATED_BODY()
	USkillDescriptionComponent();

protected:
	class UDataTable* PeppySkillTable;
	TArray<FPeppySkillData*> PeppySkillTableRows;
	class UDataTable* SpecialSkillTable;
	TArray<FSpecialSkillTable*> SpecialSkillTableRows;
	class UDataTable* ItemTable;
	TArray<FItemData*> ItemTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserWidget* HoveredWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserWidget* HoverWidgetRef;

	UFUNCTION(Blueprintcallable)
	FString SkillSpecialtyCheckValueN(int SkillIndex, float ValueN);
	UFUNCTION(Blueprintcallable)
	FString SkillSpecialtyCheckValueM(int SkillIndex, float ValueM);
	UFUNCTION(Blueprintcallable)
	FString CheckProbability(float Probability);
	UFUNCTION(Blueprintcallable)
	FString SkillGetSkillIndexByKeyword(int RowNum, FString Num);
	UFUNCTION(Blueprintcallable)
	FString SkillRedefineDescription(int RowNum);

	UFUNCTION(Blueprintcallable)
	FString SpecialtyGetSkillIndexByKeyword(int RowNum, FString Num);
	UFUNCTION(Blueprintcallable)
	FString SpecialtyRedefineDescription(int RowNum);

	UFUNCTION(Blueprintcallable)
	FString ItemCheckValueN(float ValueN);
	UFUNCTION(Blueprintcallable)
	FString ItemCheckValueM(float ValueM);
	UFUNCTION(Blueprintcallable)
	FString ItemGetSkillIndexByKeyword(int RowNum, FString Num);
	UFUNCTION(Blueprintcallable)
	FString ItemRedefineDescription(int RowNum);

	UFUNCTION(Blueprintcallable)
	void SetHoverWidgetPos(UCanvasPanel* hoverwidget, UUserWidget* backgroundBtn);
	UFUNCTION(Blueprintcallable)
	void SetSelectedSkillHoverPos(UUserWidget* hoverwidget, UUserWidget* backgroundBtn);
	UFUNCTION(Blueprintcallable)
	void SetPeppyTurnHoverWidgetPos(UCanvasPanel* hoverwidget, UUserWidget* backgroundBtn);
	UFUNCTION(Blueprintcallable)
	void SetPeppyTurnSelectedSkillHoverPos(UUserWidget* hoverwidget, UUserWidget* backgroundBtn);

	UFUNCTION(Blueprintcallable)
	void RemoveSelectedHoverWidget();
};
