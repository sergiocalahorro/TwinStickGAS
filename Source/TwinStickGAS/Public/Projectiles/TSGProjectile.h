// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TSGProjectile.generated.h"

// Forward declarations - Unreal Engine
class USphereComponent;
class UProjectileMovementComponent;

// Forward declarations - TwinStickGAS
class UPoolableComponent;
class UTSGProjectileData;

UCLASS(Abstract, Blueprintable)
class TWINSTICKGAS_API ATSGProjectile : public AActor
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:
	
	/** Sets default values for this actor's properties */
	ATSGProjectile();

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

#if WITH_EDITOR
	/** Called when a property on this object has been modified externally */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:

	/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized, only called during gameplay */
	virtual void PostInitializeComponents() override;
	
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region PROJECTILE

public:

	/** Initialize projectile's values */
	void InitializeProjectile() const;

private:

	/** Handle projectile's hit */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Handle projectile enabled */
	UFUNCTION()
	void OnEnabled();
	
	/** Handle projectile disabled */
	UFUNCTION()
	void OnDisabled();
	
private:

	/** Static mesh component */
	UPROPERTY(VisibleDefaultsOnly, Category = "AA|Projectile")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	/** Sphere component */
	UPROPERTY(VisibleDefaultsOnly, Category = "AA|Projectile")
	TObjectPtr<USphereComponent> SphereComponent;

	/** Projectile movement component */
	UPROPERTY(VisibleDefaultsOnly, Category = "AA|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	/** Poolable component */
	UPROPERTY(VisibleDefaultsOnly, Category = "AA|Projectile")
	TObjectPtr<UPoolableComponent> PoolableComponent;

	/** Projectile's data */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Projectile")
	TObjectPtr<UTSGProjectileData> ProjectileData;

#pragma endregion PROJECTILE

};
