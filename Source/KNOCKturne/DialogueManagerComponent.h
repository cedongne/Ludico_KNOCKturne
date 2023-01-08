// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "DialogueManagerComponent.generated.h"

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UDialogueManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueManagerComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
	class UDataTable* StringTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* StartIndexTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> DialogueMap;
	TArray<FDialogueString*> DialogueStrings;

public:
	UDataTable* GetStringTable();
	FString GetString(int Index);
	UDataTable* LoadDialogueTable(FString TableName, int CurrentIndex);
		
};
