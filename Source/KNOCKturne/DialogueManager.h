// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/Engine.h"
#include "Engine/DataTable.h"
#include "DialogueManager.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase {
	GENERATED_BODY()

	public:
	FDialogueData() : GroupCode("-1"), CharacterStringID("-1"), Type(-1), Image1ID("-1"), Image2ID("-1"), CutSceneID("-1"), StringID("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString GroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CharacterStringID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Image1ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Image2ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CutSceneID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString StringID;
};

UCLASS()
class KNOCKTURNE_API UDialogueManager : public UEngine
{
	GENERATED_BODY()
	
public:
	UDialogueManager();

	FDialogueData* GetPrologueDialogueData(FString RowID);

	UPROPERTY()
	class UDataTable* PrologueDialogueTable;
};
