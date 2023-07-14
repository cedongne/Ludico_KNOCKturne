// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "DialogueTableComponent.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase {
	GENERATED_BODY()
		
	
	FDialogueData() : DialogueGroupCode("-1"), CharacterGroupCode("-1"), DialogueType(0), CharacterStringID("-1"), SpeakType(-1), ImageLID("-1"), ImageRID("-1"), CutSID("-1"), StringID("-1"), Direction("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString DialogueGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CharacterGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DialogueType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CharacterStringID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SpeakType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ImageLID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ImageRID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString CutSID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString StringID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Direction;
};


UCLASS(ClassGroup = (DataTableComponent), meta = (BlueprintSpawnableComponent))
class KNOCKTURNE_API UDialogueTableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	bool IsEndedDialogueRows;

	TArray<FDialogueData*> DialogueRows;
	int32 DialogueRowsSize;
	int32 CurrentRowIndex;
	int32 StartRowIndex;

	TArray<int32> StartRandomNpcTalk;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
	class UDataTable* DialogueTable;
	class UDialogueManagerSystem* DialogueManager;

	virtual void BeginPlay() override;
	UDialogueTableComponent();
	UDialogueTableComponent(FString TablePath);

	void LoadDialogueTable(FString TableName);

	FDialogueData* GetDialogueTableRow(FString RowID);
	FString GetString(FDialogueData* DataRow);

	UFUNCTION(BlueprintCallable)
	FString GetStringOnBP(FDialogueData DataRow);

	UFUNCTION(BlueprintCallable)
	FDialogueData GetNextRowDialogueTable();

	UFUNCTION(BlueprintCallable)
	void ResetDialogueRowPointer();

	UFUNCTION(BlueprintCallable)
	void SetCurrentRow(int rowNum);

	UFUNCTION(BlueprintCallable)
	int GetCurrentRow();

	UFUNCTION(BlueprintCallable)
	int GetRowSize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Episode = "Episode1";

	UFUNCTION(BlueprintCallable)
	void GetRandomTalkIndex(FString NpcName);

	UFUNCTION(BlueprintCallable)
	void EmptyTArray();

	UFUNCTION(BlueprintCallable)
	bool NextDialogueTypeIs1();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentDialogueType();

	UFUNCTION(BlueprintCallable)
	void SkipDialogue();

	UFUNCTION(BlueprintCallable)
	void SetIsEndedDialogueRows(bool tf);

	UFUNCTION(BlueprintCallable)
	FString RandomLoadingText();

	UFUNCTION(BlueprintCallable)
	void GetDreamFragmentTalk();

	UFUNCTION(BlueprintCallable)
	void CancelDreamFragmentChocie();
};