﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TSGProjectileData.generated.h"

// Forward declarations - Unreal Engine
class USoundBase;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class TWINSTICKGAS_API UTSGProjectileData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/** Asset for this projectile's static mesh */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> StaticMesh;

	/** Particles attached to this projectile */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> TracerParticles;

	/** Particles spawned when the projectile impacts on something */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ImpactParticles;

	/** Sound played when the projectile impacts on something */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ImpactSound;

	/** Base damage value */
	UPROPERTY(EditDefaultsOnly)
	float BaseDamage;
	
	/** Damage radius */
	UPROPERTY(EditDefaultsOnly)
	float DamageRadius;
	
	/** Effects applied on this projectile's radial damage */
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	/** Object types affected by this projectile's radial damage */
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> RadialDamageQueryTypes;

	/** Trace channel used on this projectile's radial damage */
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> RadialDamageTraceType;

	/** Initial speed */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 0.f, ClampMin = 0.f, ForceUnits = "cm/s"))
	float InitialSpeed = 1000.f;

	/** Maximum speed */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 0.f, ClampMin = 0.f, ForceUnits = "cm/s"))
	float MaxSpeed = 1000.f;

	/** Gravity scale */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 0.f, ClampMin = 0.f))
	float GravityScale = 0.f;

	/** Whether initial velocity is set in local space */
	UPROPERTY(EditDefaultsOnly)
	bool bInitialVelocityInLocalSpace = true;

	/** Whether rotation follows velocity */
	UPROPERTY(EditDefaultsOnly)
	bool bRotationFollowsVelocity = true;

	/** Whether projectile should bounce */
	UPROPERTY(EditDefaultsOnly)
	bool bShouldBounce = false;
	
	/** Bounciness */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = 0.f, ClampMin = 0.f, EditCondition = "bShouldBounce", EditConditionHides))
	float Bounciness = 0.f;
};
