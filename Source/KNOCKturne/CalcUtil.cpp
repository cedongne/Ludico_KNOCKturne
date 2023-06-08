// Fill out your copyright notice in the Description page of Project Settings.


#include "CalcUtil.h"

CalcUtil::CalcUtil()
{
}

CalcUtil::~CalcUtil()
{
}

int CalcUtil::RandEvenNumberInRange(int min, int max) {
	srand((unsigned int)time(NULL));

	int randomNum = rand();
	int range = (max - min) / 2;

	return ((randomNum % range) * 2) + min;
}