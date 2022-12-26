// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"
#include "KNOCKturneObjectPool.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KNOCKTURNE_API UKNOCKturneObjectPool : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UKNOCKturneObjectPool();

	UFUNCTION(BlueprintCallable, Category = "ObjectPool")
	APooledObject* SpawnPooledObject();
	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);
	UFUNCTION()
	void OnPooledObjectTouchDespawn(APooledObject* PoolActor);

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	TSubclassOf<class APooledObject> PooledObjectSubclass;
	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	int PoolSize = 10;
	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	float PooledObjectLifeSpan = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<APooledObject*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;

	int FirstIndex = 0;
	int LastIndex = 0;
};
