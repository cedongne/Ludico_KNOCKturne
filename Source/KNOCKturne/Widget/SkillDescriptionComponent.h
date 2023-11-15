// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "Components/Button.h"

#include "SkillDescriptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API USkillDescriptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillDescriptionComponent();

protected:
	class UDataTable* PeppySkillTable;
	TArray<FPeppySkillData*> PeppySkillTableRows;
	class UDataTable* SpecialSkillTable;
	TArray<FSpecialSkillData*> SpecialSkillTableRows;
	class UDataTable* ItemTable;
	TArray<FItemData*> ItemTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;

public:	
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
	void SetHoverWidgetPos(UUserWidget* hoverwidget, UButton* backgroundBtn);
	UFUNCTION(Blueprintcallable)
	void SetSelectedSkillHoverPos(UUserWidget* hoverwidget, UButton* backgroundBtn);
	UFUNCTION(Blueprintcallable)
	void SetPeppyTurnHoverWidgetPos(UUserWidget* hoverwidget, UButton* backgroundBtn);
	UFUNCTION(Blueprintcallable)
	void SetPeppyTurnSelectedSkillHoverPos(UUserWidget* hoverwidget, UButton* backgroundBtn);
};
