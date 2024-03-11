// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameMode/KNOCKturneGameState.h"
#include "BattleManagerSystem.generated.h"

UCLASS()
class KNOCKTURNE_API UBattleManagerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	AKNOCKturneGameState* KNOCKturneGameState;
	
public:
	UBattleManagerSystem();

	class ABattleManager* BattleManager;

	void LoadGameState(AGameStateBase* GameState);
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	class UBattleTableManagerSystem* BattleTableManagerSystem = nullptr;
	class UActorManagerSystem* ActorManagerSystem = nullptr;

	void LoadBattleTableManagerSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
	bool VisibleBossSkillHitArea = false;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	TArray<class UWidgetComponent*> CurBossSkillHitArea;

	UFUNCTION(BlueprintCallable)
	void SetTimerUnvisibleHitArea();

	/*������-���� �� �غ�*/
	// ������ ���������� ������ ��ų
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString FinalSpecialSkill = "Skill_Special_Pretendnotsick"; // ���������� ������ Ư����

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString FinalItem; // ���������� ������ ������

	/*���� ��*/

	// ���� �Ͽ��� ������ ��ų ������ �̸�-��ų ����

	// ���� �Ͽ��� ������ ��ų ���� ����Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AActor>> SelectedSkillActorClassList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> SelectedSkillIconNameList;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isSkipPeppyTurn = false;


	// �����ۺ� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isPrologue = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DreamFragmentCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DreamDiaryOpenRow = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool GetDreamFragment = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isDreamDiaryUpdated = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isBattleFail = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool RightafterBattleClear = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> ItemCountList;

	UFUNCTION(BlueprintCallable)
	void UpdateDreamDiaryWhenGameOver();
	UFUNCTION(BlueprintCallable)
	void UpdateDreamDiaryWhenGameClear();
	UFUNCTION(BlueprintCallable)
	void GetDreamFragmentAfterBattle();

	// Round ���� �׸�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Round = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LastRoundBossHpRatio = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ReducedEP = 0;
	void UpdateRoundInfo();

	// 스탠스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString BossStanceID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString ResponseStanceID;

	TArray<FString> BossStances = {
		"Obsession",
		"Longing"
	};

	// '아름다운 별빛' 사용 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UseStarlightNum = 0;
};