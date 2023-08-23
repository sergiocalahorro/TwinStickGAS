// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal Engine
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// ObjectPool
#include "Utils/ActorArray.h"
#include "Utils/IntegerArray.h"

#include "ObjectPoolComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OBJECTPOOL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region INITIALIZATION

public:

	/** Sets default values for this component's properties */
	UObjectPoolComponent();

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

protected:

	/** Called when game starts */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region OBJECT_POOL

public:

	/** Create object pools */
	UFUNCTION(BlueprintCallable)
	void CreatePools();

	/** Create object pool per class */
	UFUNCTION(BlueprintCallable)
	void CreatePoolPerClass(TSubclassOf<AActor> PoolableObjectClass);

	/** Get object from class's pool */
	UFUNCTION(BlueprintCallable)
	AActor* GetPooledObject(TSubclassOf<AActor> PoolableObjectClass, const FTransform& SpawnTransform);

private:

	/** Whether pools should be created at start */
	UPROPERTY(EditDefaultsOnly)
	bool bCreatePoolsAtStart = true;

	/** Object pool size per class */
	UPROPERTY(EditDefaultsOnly, Category = "AA|ObjectPool")
	TMap<TSubclassOf<AActor>, int32> PoolSizePerClass;

	/** Object pool per class */
	UPROPERTY()
	TMap<TSubclassOf<AActor>, FActorArray> PoolPerClass;

	/** Object pool per class's used indices */
	UPROPERTY()
	TMap<TSubclassOf<AActor>, FIntegerArray> PoolPerClassUsedIndices;

#pragma endregion OBJECT_POOL
};