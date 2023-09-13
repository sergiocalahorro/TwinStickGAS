// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/ObjectPoolComponent.h"

// ObjectPool
#include "Core/PoolableComponent.h"

#pragma region INITIALIZATION

/** Sets default values for this component's properties */
UObjectPoolComponent::UObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

/** Called when game starts */
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bCreatePoolsAtStart)
	{
		CreatePools();
	}
}

#pragma endregion OVERRIDES

#pragma region OBJECT_POOL

/** Create object pools */
void UObjectPoolComponent::CreatePools()
{
	if (PoolSizePerClass.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("UObjectPoolComponent::CreatePools - Pools in Actor %s are empty"), *GetNameSafe(GetOwner()));
		return;
	}
	
	if (!PoolPerClass.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("UObjectPoolComponent::CreatePools - Pools in Actor %s are already created"), *GetNameSafe(GetOwner()));
		return;
	}
	
	TArray<TSubclassOf<AActor>> ObjectPoolsClasses;
	PoolSizePerClass.GetKeys(ObjectPoolsClasses);

	for (TSubclassOf<AActor> PoolableObjectClass : ObjectPoolsClasses)
	{
		CreatePoolPerClass(PoolableObjectClass);
	}
}

/** Create object pool per class */
void UObjectPoolComponent::CreatePoolPerClass(TSubclassOf<AActor> PoolableObjectClass)
{
	if (!PoolSizePerClass.Contains(PoolableObjectClass))
	{
		UE_LOG(LogTemp, Error, TEXT("UObjectPoolComponent::CreatePoolPerClass - Pool in Actor %s for class %s doesn't exist"), *GetNameSafe(GetOwner()), *GetNameSafe(PoolableObjectClass));
		return;
	}
	
	const int32 PoolSize = *PoolSizePerClass.Find(PoolableObjectClass);

	FActorArray ActorArray;
	if (PoolPerClass.Contains(PoolableObjectClass))
	{
		ActorArray = *PoolPerClass.Find(PoolableObjectClass);
	}
	
	for (int32 i = 0; i < PoolSize; i++)
	{
		if (AActor* Object = GetWorld()->SpawnActor<AActor>(PoolableObjectClass, FTransform::Identity))
		{
			if (UPoolableComponent* PoolableComponent = Cast<UPoolableComponent>(Object->FindComponentByClass(UPoolableComponent::StaticClass())))
			{
				PoolableComponent->Disable();
				ActorArray.Actors.Add(Object);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("UObjectPoolComponent::CreatePoolPerClass - Pool in Actor %s couldn't be created because Actor %s is not Poolable"), *GetNameSafe(GetOwner()), *GetNameSafe(Object));
				return;
			}
		}
	}
	
	PoolPerClass.Add(PoolableObjectClass, ActorArray);
}

/** Get object from class's pool */
AActor* UObjectPoolComponent::GetPooledObject(TSubclassOf<AActor> PoolableObjectClass, const FTransform& SpawnTransform)
{
	if (PoolPerClass.Contains(PoolableObjectClass))
	{
		TArray<AActor*> Pool = PoolPerClass.Find(PoolableObjectClass)->Actors;
		for (int32 i = 0; i < Pool.Num(); i++)
		{
			AActor* ObjectInPool = Pool[i];
			if (UPoolableComponent* PoolableComponent = Cast<UPoolableComponent>(ObjectInPool->FindComponentByClass(UPoolableComponent::StaticClass())))
			{
				if (!PoolableComponent->IsEnabled())
				{
					ObjectInPool->SetActorTransform(SpawnTransform);
					PoolableComponent->Enable();
					return ObjectInPool;
				}
			}
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("UObjectPoolComponent::GetPooledObject - Failed to retrive object of Class %s, please consider increasing the pool's size"), *GetNameSafe(PoolableObjectClass));
	return nullptr;
}

#pragma endregion OBJECT_POOL