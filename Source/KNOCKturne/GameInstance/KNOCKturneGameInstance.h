// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "KNOCKturneGameInstance.generated.h"

UCLASS()
class KNOCKTURNE_API UKNOCKturneGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UKNOCKturneGameInstance();

	virtual void Init() override;
};
