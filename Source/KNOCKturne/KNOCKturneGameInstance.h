// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "KNOCKturneGameInstance.generated.h"

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
class KNOCKTURNE_API UKNOCKturneGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UKNOCKturneGameInstance();

	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = StatData)
	FPeppyStatData CurPeppyStat;

	FPeppyStatData* GetPeppyStatData(FString DataType);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = StatData)
	FTransform PeppyTransform;
	
private:
	UPROPERTY()
	class UDataTable* PeppyStatDataTable;
};
