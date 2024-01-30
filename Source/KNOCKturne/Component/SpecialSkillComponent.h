// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "SpecialSkillComponent.generated.h"

USTRUCT(BlueprintType)
struct FSpecialSkillTable : public FTableRowBase {
	GENERATED_BODY()

	FSpecialSkillTable() : Skill_Index(-1), Probability_1(0.0f), SpecialSkill_Target(-1), Value1N(0), Value1M(0), Value1T(0),
		BuffCode("-1"), EnergyCost(0), CoolTime(0), SpecialSkillIcon(nullptr), SpecialSkillDescript("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Skill_Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Probability_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SpecialSkill_Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value1N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value1M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Value1T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 EnergyCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 CoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> SpecialSkillIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SpecialSkillDescript;
};

USTRUCT(BlueprintType)
struct FSpecialSkillData {
	GENERATED_BODY()

public:
	FSpecialSkillData() : Skill_Index(-1), Probability_1(0.0f), SpecialSkill_Target(-1), Value1N(0), Value1M(0), Value1T(0),
		BuffCode("-1"), EnergyCost(0), CoolTime(0) {}

	FSpecialSkillData(int32 Skill_Index, float Probability_1, int32 SpecialSkill_Target, float Value1N, float Value1M, float Value1T, FString BuffCode, int32 EnergyCost, int32 CoolTime) {
		this->Skill_Index = Skill_Index;
		this->Probability_1 = Probability_1;
		this->Value1N = Value1N;
		this->Value1M = Value1M;
		this->Value1T = Value1T;
		this->BuffCode = BuffCode;
		this->EnergyCost = EnergyCost;
		this->CoolTime = CoolTime;
	}

	FSpecialSkillData(FSpecialSkillTable* SpecialSkillTableData) {
		this->Skill_Index = SpecialSkillTableData->Skill_Index;
		this->Probability_1 = SpecialSkillTableData->Probability_1;
		this->Value1N = SpecialSkillTableData->Value1N;
		this->Value1M = SpecialSkillTableData->Value1M;
		this->Value1T = SpecialSkillTableData->Value1T;
		this->BuffCode = SpecialSkillTableData->BuffCode;
		this->EnergyCost = SpecialSkillTableData->EnergyCost;
		this->CoolTime = SpecialSkillTableData->CoolTime;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Skill_Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Probability_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SpecialSkill_Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value1N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value1M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Value1T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 EnergyCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 CoolTime;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API USpecialSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpecialSkillComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class UBattleManagerSystem* BattleManagerSystem;
	FSpecialSkillData* SpecialSkillData;

private:
	UPROPERTY()
	class UDataTable* SpecialSkillTable;

	bool CanUseSpecialSkill = true;

public:	
		
};
