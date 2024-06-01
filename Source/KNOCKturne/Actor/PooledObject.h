// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectTouchDespawn, APooledObject*, PoolActor);

UCLASS()
class KNOCKTURNE_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;
	FOnPooledObjectTouchDespawn OnPooledObjectTouchDespawn;

	UFUNCTION(BlueprintCallable, Category = "PooledObject")
	void Deactivate();
	UFUNCTION(BlueprintCallable, Category = "PooledObject")
	void TouchDeactivate();

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);

	bool IsActive();
	int GetPoolIndex();

protected:
	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;

	FTimerHandle LifeSpanTimer;
};
