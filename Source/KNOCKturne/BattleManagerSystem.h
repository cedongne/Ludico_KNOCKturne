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

	// IconRowMap 초기화
	void InitSkillIconRowMap();

	// IconRowMap 초기화
	void InitSpecialtyIconRowMap();

	// IconRowMap 초기화
	void InitItemIconRowMap();

	// IconSkillActorMap 초기화
	void InitIconSkillActorMap();

	// 아리송한 감정파악
	TSubclassOf<AActor> AmbiguousEmotion_Ref;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LeftCurTurnTime;

	void InitializeFootholdObject();

	UFUNCTION(BlueprintCallable)
	void SpawnFoothold();

	UFUNCTION(BlueprintCallable)
	void SetTimerUnvisibleHitArea();


	/*보따리-전투 전 준비*/
	// 허브월드 보따리에서 선택한 스킬
	TArray<int32> SelectedSkillCodeList;

	// 허브월드 보따리에서 선택한 스킬 리스트 크기 설정
	UFUNCTION(BlueprintCallable)
	void SetSizeOfSelectedSkillCodeList(int32 size);

	// 허브월드 보따리에서 선택한 스킬 리스트 크기 가져오기
	UFUNCTION(BlueprintCallable)
	int32 GetSizeOfSelectedSkillCodeList();

	// 허브월드 보따리에서 선택한 스킬 리스트 설정
	UFUNCTION(BlueprintCallable)
	void SetOneSelectedSkillCodeList(int32 index, int32 value);

	// 허브월드 보따리에서 선택한 스킬 리스트 가져오기
	UFUNCTION(BlueprintCallable)
	int32 GetOneSelectedSkillCodeInList(int32 index);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetSelectedSkillCodeList(); 


	// 보따리에서 선택한 스킬 아이콘 이름-행 번호
	TMap<FString, int32> SkillIconRowMap;

	// 아이콘 이름으로 스킬 행 찾기
	UFUNCTION(BlueprintCallable)
	int32 FindSkillRow(FString IconName);


	// 보따리에서 선택한 특수기 아이콘 이름-행 번호
	TMap<FString, int32> SpecialtyIconRowMap;

	// 아이콘 이름으로 아이템 행 찾기
	UFUNCTION(BlueprintCallable)
	int32 FindSpecialtyRow(FString IconName);


	// 보따리에서 선택한 특수기 아이콘 이름-행 번호
	TMap<FString, int32> ItemIconRowMap;

	// 아이콘 이름으로 아이템 행 찾기
	UFUNCTION(BlueprintCallable)
	int32 FindItemRow(FString IconName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, TSubclassOf<AActor>> IconSkillActorMap;
//	TMap<FString, UClass*> IconSkillActorMap;

	/*페피 턴*/

	// 페피 턴에서 선택한 스킬 아이콘 이름-스킬 액터

	// 페피 턴에서 선택한 스킬 액터 리스트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AActor>> SelectedSkillActorClassList;

	// 아이콘 이름으로 스킬 액터 찾기
	UFUNCTION(BlueprintCallable)
	TSubclassOf<AActor> FindSkillActor(FString IconName);

	// 스킬 액터 클래스 리스트 원소 추가
	UFUNCTION(BlueprintCallable)
	void AddSelectedSkillActorClassList(TSubclassOf<AActor> SkillActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DraggedIndex = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 OverlappedIndex = -1;
};