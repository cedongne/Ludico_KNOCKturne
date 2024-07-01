// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/KNOCKturneSaveGame.h"

UKNOCKturneSaveGame::UKNOCKturneSaveGame()
{
	isPrologue = false;
	isSkippedBeforeBattleSequence = false;
	CanSkipBeforeBattleSequence = false;
	DreamFragmentCount = 0;
	DreamDiaryOpenRow = 0;
	GetDreamFragment = false;
	isDreamDiaryUpdated = false;
	isBattleFail = false;
	RightafterBattleClear = false;
	ItemCountList.Init(0, 6);
	TryBattleCount = 0;
	TotalPlayTime = 0;
	BattleClearTime = 0;
	isAfterCredit = false;
	SelectedSkillCodeList.Init(0, 8);
	FinalSpecialSkill = "";
	FinalItem = "";

	isNpcGiveDreamFragment.Add("DreamM", false);
	isNpcGiveDreamFragment.Add("Rabbit", false);
	isNpcGiveDreamFragment.Add("Lake", false);

	NpcNormalTalkCount.Add("DreamM", 0);
	NpcNormalTalkCount.Add("Rabbit", 0);
	NpcNormalTalkCount.Add("Lake", 0);
}
