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
	void InitIconRowMap();

	// IconSkillActorMap �ʱ�ȭ
	void InitIconSkillActorMap();

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
	TMap<FString, int32> IconRowMap;

	// ������ �̸����� �� ã��
	UFUNCTION(BlueprintCallable)
	int FindRow(FString IconName);



	/*���� ��*/

	// ���� �Ͽ��� ������ ��ų ������ �̸�-��ų ����
	TMap<FString, AActor> IconSkillActorMap;

	// ���� �Ͽ��� ������ ��ų ���� ����Ʈ
	TArray<AActor*> SelectedSkillActor;

	// ������ �̸����� ��ų ���� ã��
	UFUNCTION(BlueprintCallable)
	AActor* FindSkillActor(FString IconName);

	// ��ų ���� ����Ʈ ���� �߰�
	UFUNCTION(BlueprintCallable)
	void AddSelectedSkillActor(AActor* SkillActor);
};