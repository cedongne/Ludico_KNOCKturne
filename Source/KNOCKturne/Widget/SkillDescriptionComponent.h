// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/DialogueManagerSystem.h"

#include "SkillDescriptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API USkillDescriptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillDescriptionComponent();

protected:
	class UDataTable* ItemTable;
	TArray<FItemData*> ItemTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;

public:	
	UFUNCTION(Blueprintcallable)
	FString ItemCheckValueN(float ValueN);
	UFUNCTION(Blueprintcallable)
	FString ItemCheckValueM(float ValueM);
	UFUNCTION(Blueprintcallable)
	FString ItemGetSkillIndexByKeyword(int RowNum, FString Num);
	UFUNCTION(Blueprintcallable)
	FString ItemRedefineDescription(int RowNum);
		
};
