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
	TArray<int32> SelectedSkills1;

	// ������ ���������� ������ ��ų ����Ʈ ũ�� ����
	UFUNCTION(BlueprintCallable)
	void SetSizeOfSelectedSkills1(int size);

	// ������ ���������� ������ ��ų ����Ʈ ũ�� ��������
	UFUNCTION(BlueprintCallable)
	int GetSizeOfSelectedSkills1();

	// ������ ���������� ������ ��ų ����Ʈ ����
	UFUNCTION(BlueprintCallable)
	void SetOneSelectedSkills1(int index, int value);

	// ������ ���������� ������ ��ų ����Ʈ ��������
	UFUNCTION(BlueprintCallable)
	int GetOneSelectedSkills1(int index);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetSelectedSkills1(); 


	// ���������� ������ ��ų ������ �̸�-�� ��ȣ
	TMap<FString, int32> SkillIconRowMap;

	// ������ �̸����� ��ų �� ã��
	UFUNCTION(BlueprintCallable)
	int FindSkillRow(FString IconName);


	// ���������� ������ Ư���� ������ �̸�-�� ��ȣ
	TMap<FString, int32> SpecialtyIconRowMap;

	// ������ �̸����� ������ �� ã��
	UFUNCTION(BlueprintCallable)
	int FindSpecialtylRow(FString IconName);


	// ���������� ������ Ư���� ������ �̸�-�� ��ȣ
	TMap<FString, int32> ItemIconRowMap;

	// ������ �̸����� ������ �� ã��
	UFUNCTION(BlueprintCallable)
	int FindItemlRow(FString IconName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, TSubclassOf<AActor>> IconSkillActorMap;
//	TMap<FString, UClass*> IconSkillActorMap;
	/*���� ��*/

	//// ���� �Ͽ��� ������ ��ų ������ �̸�-��ų ����

	//// ���� �Ͽ��� ������ ��ų ���� ����Ʈ
	//TArray<AActor*> SelectedSkillActor;

	//// ������ �̸����� ��ų ���� ã��
	//UFUNCTION(BlueprintCallable)
	//AActor* FindSkillActor(FString IconName);

	//// ��ų ���� ����Ʈ ���� �߰�
	//UFUNCTION(BlueprintCallable)
	//void AddSelectedSkillActor(AActor* SkillActor);
};