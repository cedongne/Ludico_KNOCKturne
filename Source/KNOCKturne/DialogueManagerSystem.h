// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueManagerSystem.generated.h"

USTRUCT(BlueprintType)
struct FStartIndex : public FTableRowBase {
	GENERATED_BODY()

public:
	FStartIndex() : StringIndex(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 StringIndex;
};

USTRUCT(BlueprintType)
struct FDialogueString : public FTableRowBase {
	GENERATED_BODY()

public:
	FDialogueString() : KOR("") {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "String")
	FString KOR;
};

UCLASS()
class KNOCKTURNE_API UDialogueManagerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
	class UDataTable* StringTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* StartIndexTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> DialogueMap;
	TArray<FDialogueString*> DialogueStrings;
	
public:
	UDialogueManagerSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UDataTable* LoadDialogueTable(FString TableName, int& Index);

	UDataTable* GetStringTable();
};
