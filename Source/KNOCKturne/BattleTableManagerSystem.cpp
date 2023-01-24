// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTableManagerSystem.h"

UBattleTableManagerSystem::UBattleTableManagerSystem() {
	FString BossSkilTablePath = TEXT("/Game/Assets/DataTable/Ep1BossSkillTable.Ep1BossSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSKILLTABLE(*BossSkilTablePath);
	NTCHECK(DT_BOSSKILLTABLE.Succeeded());

	BossSkillTable = DT_BOSSKILLTABLE.Object;
}