// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "SpecialSkillComponent.generated.h"

UENUM(BlueprintType)
enum class ESpecialSkillType : uint8 {
	Wakeup		UMETA(DisplayName = "Wakeup"),
	Gatherenergy		UMETA(DisplayName = "Gatherenergy"),
	Positivethinking	UMETA(DisplayName = "Positivethinking"),
	Narrowescape		UMETA(DisplayName = "Narrowescape"),
	Pretendnotsick	UMETA(DisplayName = "Pretendnotsick"),
	Twolives		UMETA(DisplayName = "Twolives"),
};

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API USpecialSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpecialSkillComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class APeppyController* PeppyController;
	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UActorManagerSystem* ActorManagerSystem;
	FSpecialSkillTable* SpecialSkillData;

private:

	UPROPERTY()
	class UDataTable* SpecialSkillTable;

	float TempDelayTime;

public:	
	UFUNCTION(BlueprintCallable)
	void CreateSpecialSkillData();

	UFUNCTION(BlueprintCallable)
	bool CheckCanUseSpecialSkill(float DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	bool DelayWithDeltaTime(float DelayTime, float DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	bool TryUseSpecialSkill();
};
