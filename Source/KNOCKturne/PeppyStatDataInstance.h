// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "PeppyStatDataInstance.generated.h"

USTRUCT(BlueprintType)
struct FPeppyStatData : public FTableRowBase {
	GENERATED_BODY()
	
public:
	FPeppyStatData() : MaxHP(100), MaxEP(50), SlidingCooldown(3), DamageDecrease(0), Turn(50) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxEP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SlidingCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DamageDecrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Turn;
};

UCLASS()
class KNOCKTURNE_API UPeppyStatDataInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPeppyStatDataInstance();

	virtual void Init() override;

	FPeppyStatData* GetPeppyStatData(FString DataType);

private:
	UPROPERTY()
	class UDataTable* PeppyStatDataTable;
};
