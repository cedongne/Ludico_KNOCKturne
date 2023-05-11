// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattleManagerSystem.generated.h"

/**
 * 
 */


UCLASS()
class KNOCKTURNE_API UBattleManagerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UBattleManagerSystem();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
	bool VisibleBossSkillHitArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	class UStaticMeshComponent* CurBossSkillHitArea;

	UClass* FootholdClass;
	TSubclassOf<AActor> FootholdSubclass;
	AActor* FootholdObject;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LeftCurTurnTime;

	void InitializeFootholdObject();

	UFUNCTION(BlueprintCallable)
	void SpawnFoothold();

	UFUNCTION(BlueprintCallable)
	void SetTimerUnvisibleHitArea();



	// 허브월드 보따리에서 선택한 스킬
	TArray<int32> SelectedSkills1;

	// 허브월드 보따리에서 선택한 스킬 리스트 크기 설정
	UFUNCTION(BlueprintCallable)
	void SetSizeOfSelectedSkills1(int size);

	// 허브월드 보따리에서 선택한 스킬 리스트 크기 가져오기
	UFUNCTION(BlueprintCallable)
	int GetSizeOfSelectedSkills1();

	// 허브월드 보따리에서 선택한 스킬 리스트 설정
	UFUNCTION(BlueprintCallable)
	void SetOneSelectedSkills1(int index, int value);

	// 허브월드 보따리에서 선택한 스킬 리스트 가져오기
	UFUNCTION(BlueprintCallable)
	int GetOneSelectedSkills1(int index);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetSelectedSkills1(); 
};