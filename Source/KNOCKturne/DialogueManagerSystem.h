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
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
