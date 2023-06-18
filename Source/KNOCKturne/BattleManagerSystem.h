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

	// IconRowMap �ʱ�ȭ
	void InitSkillIconRowMap();

	// IconRowMap �ʱ�ȭ
	void InitSpecialtyIconRowMap();

	// IconRowMap �ʱ�ȭ
	void InitItemIconRowMap();

	// IconSkillActorMap �ʱ�ȭ
	void InitIconSkillActorMap();

	// �Ƹ����� �����ľ�
	TSubclassOf<AActor> AmbiguousEmotion_Ref;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LeftCurTurnTime;

	void InitializeFootholdObject();

	UFUNCTION(BlueprintCallable)
	void SpawnFoothold();

	UFUNCTION(BlueprintCallable)
	void SetTimerUnvisibleHitArea();


	/*������-���� �� �غ�*/
	// ������ ���������� ������ ��ų
	TArray<int32> SelectedSkillCodeList;

	// ������ ���������� ������ ��ų ����Ʈ ũ�� ����
	UFUNCTION(BlueprintCallable)
	void SetSizeOfSelectedSkillCodeList(int32 size);

	// ������ ���������� ������ ��ų ����Ʈ ũ�� ��������
	UFUNCTION(BlueprintCallable)
	int32 GetSizeOfSelectedSkillCodeList();

	// ������ ���������� ������ ��ų ����Ʈ ����
	UFUNCTION(BlueprintCallable)
	void SetOneSelectedSkillCodeList(int32 index, int32 value);

	// ������ ���������� ������ ��ų ����Ʈ ��������
	UFUNCTION(BlueprintCallable)
	int32 GetOneSelectedSkillCodeInList(int32 index);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetSelectedSkillCodeList(); 


	// ���������� ������ ��ų ������ �̸�-�� ��ȣ
	TMap<FString, int32> SkillIconRowMap;

	// ������ �̸����� ��ų �� ã��
	UFUNCTION(BlueprintCallable)
	int32 FindSkillRow(FString IconName);


	// ���������� ������ Ư���� ������ �̸�-�� ��ȣ
	TMap<FString, int32> SpecialtyIconRowMap;

	// ������ �̸����� ������ �� ã��
	UFUNCTION(BlueprintCallable)
	int32 FindSpecialtyRow(FString IconName);


	// ���������� ������ Ư���� ������ �̸�-�� ��ȣ
	TMap<FString, int32> ItemIconRowMap;

	// ������ �̸����� ������ �� ã��
	UFUNCTION(BlueprintCallable)
	int32 FindItemRow(FString IconName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, TSubclassOf<AActor>> IconSkillActorMap;
//	TMap<FString, UClass*> IconSkillActorMap;

	/*���� ��*/

	// ���� �Ͽ��� ������ ��ų ������ �̸�-��ų ����

	// ���� �Ͽ��� ������ ��ų ���� ����Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AActor>> SelectedSkillActorClassList;

	// ������ �̸����� ��ų ���� ã��
	UFUNCTION(BlueprintCallable)
	TSubclassOf<AActor> FindSkillActor(FString IconName);

	// ��ų ���� Ŭ���� ����Ʈ ���� �߰�
	UFUNCTION(BlueprintCallable)
	void AddSelectedSkillActorClassList(TSubclassOf<AActor> SkillActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DraggedIndex = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 OverlappedIndex = -1;
};