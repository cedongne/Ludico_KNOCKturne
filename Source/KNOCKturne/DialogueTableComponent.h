// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "DialogueTableComponent.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase {
	GENERATED_BODY()

public:
	FDialogueData() : GroupCode("-1"), CharacterStringID("-1"), Type(-1), ImageLID("-1"), ImageRID("-1"), CutSID("-1"), StringID("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString GroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CharacterStringID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ImageLID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ImageRID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CutSID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString StringID;
};

USTRUCT(BlueprintType)
struct FDialogueString : public FTableRowBase{
	GENERATED_BODY()
	
public:
	FDialogueString() : KOR("") {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "String")
	FString KOR;
};

UCLASS( ClassGroup=(DataTableComponent), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UDialogueTableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
	class UDataTable* DialogueTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
	class UDataTable* StringTable;

public:
	UDialogueTableComponent();
	UDialogueTableComponent(FString TablePath);

	void LoadDialogueTable(FString TablePath);

	FDialogueData* GetDialogueTableRow(FString RowID);
	FString GetString(FDialogueData* DataRow);
};
