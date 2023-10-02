// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonSkillActor.h"
#include "PeppySkillActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API APeppySkillActor : public ACommonSkillActor
{
	GENERATED_BODY()
	
public:
	APeppySkillActor();

private:
//	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Animation")
//	UAnimMontage* SkillAnimMontage;


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Initialize() override;

	void LoadSkillDataFromDataTable();

	FPeppySkillData SkillData;

	UFUNCTION(BlueprintCallable)
	bool TryOperateSkillEffect(ESkillUsingType SkillUsingType) override;

	ESkillUsingType CurSkillUsingType = ESkillUsingType::Sequential;
};
