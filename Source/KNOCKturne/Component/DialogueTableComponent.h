// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "GameMode/KNOCKturneGameState.h"

#include "Actor/NPC.h"

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

USTRUCT(BlueprintType)
struct FDreamDiaryData : public FTableRowBase {
	GENERATED_BODY()


		FDreamDiaryData() : DiaryGroupCode("-1"), DreamDiaryPage(0), DreamDiaryOpenType(-1), DreamDiaryStringID("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString DiaryGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DreamDiaryPage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DreamDiaryOpenType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString DreamDiaryStringID;
};


UCLASS(ClassGroup = (DataTableComponent), meta = (BlueprintSpawnableComponent))
class KNOCKTURNE_API UDialogueTableComponent : public UActorComponent
{
	GENERATED_BODY()

	AKNOCKturneGameState* KNOCKturneGameState;

protected:
	TArray<FDialogueData*> DialogueRows;
	int32 DialogueRowsSize;
	int32 CurrentRowIndex;
	int32 StartRowIndex;

	TArray<int32> StartRandomNpcTalk;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
		bool IsEndedDialogueRows;

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
	void SetRandomTalkIndex(ANPC* InteractingNpc, FString NpcName);

	UFUNCTION(BlueprintCallable)
	void GetNormalRandomTalkIndexs(ANPC* InteractingNpc, FString NpcName);

	UFUNCTION(BlueprintCallable)
	void GetGiveFragmentRandomTalkIndexs(ANPC* InteractingNpc, FString NpcName);

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
	void SetDreamFragmentDialogueIndex();

	UFUNCTION(BlueprintCallable)
	void SetAfterBattleDialogueIndex();

	UFUNCTION(BlueprintCallable)
	void SetAfterBattleDialogueinHubworldIndex();

	UFUNCTION(BlueprintCallable)
	void SetAfterBattleFailDialogueIndex();

	UFUNCTION(BlueprintCallable)
	void SetBattleFailDiaryDialogueIndex();

	UFUNCTION(BlueprintCallable)
	void SetBattleFailFragmentDialogueIndex();

	UFUNCTION(BlueprintCallable)
	void SetDialogueIndexByGroupCode(FString GroupCode);

	UFUNCTION(BlueprintCallable)
	bool isRedefineNeededLine(FString RowName);
};