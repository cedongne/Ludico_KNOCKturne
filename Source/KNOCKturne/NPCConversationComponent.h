// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "NPCConversationComponent.generated.h"

USTRUCT(BlueprintType)
struct FNPCConversation : public FTableRowBase {
	GENERATED_BODY()

public:
	FNPCConversation() : EpisodeGroupCode("-1"), CharacterGroupCode("-1"), StartType("-1"), CharacterName("-1"), Type(-1), Image1ID("-1"), Image2ID("-1"), CutSceneID("-1"), StringID("-1"), NextDialogID("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString EpisodeGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString CharacterGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString StartType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString CharacterName;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString NextDialogID;
};

UCLASS(ClassGroup = (DataTableComponent), meta = (BlueprintSpawnableComponent))
class KNOCKTURNE_API UNPCConversationComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
		class UDataTable* DialogueTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Table")
		class UDataTable* StringTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
		bool IsEndedDialogueRows;

	TArray<FNPCConversation*> DialogueRows;
	int32 DialogueRowsSize;
	int32 CurrentRow;

public:
	UNPCConversationComponent();
	UNPCConversationComponent(FString TablePath);

	void LoadDialogueTable(FString TablePath);

	FNPCConversation* GetDialogueTableRow(FString RowID);

	UFUNCTION(BlueprintCallable)
		FNPCConversation GetNextRowDialogueTable();

	UFUNCTION(BlueprintCallable)
		void ResetDialogueRowPointer();
};