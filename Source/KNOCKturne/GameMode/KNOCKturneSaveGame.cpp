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
}
