// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"

// Headers - TwinStickGAS
#include "TSGBaseAbility.h"

#include "TSGAbility_Shoot.generated.h"

// Forward declarations - TwinStickGAS
class ATSGProjectile;
class UTSGProjectileData;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TWINSTICKGAS_API UTSGAbility_Shoot : public UTSGBaseAbility
{
	GENERATED_BODY()

#pragma region OVERRIDES

protected:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

#pragma endregion OVERRIDES

#pragma region SHOOT

private:

	/** Shoot projectile */
	UFUNCTION()
	void Shoot();

protected:

	/** Projectile to shoot's class */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Projectile")
	TSubclassOf<ATSGProjectile> ProjectileClass;
	
	/** Fire rate to shoot projectiles */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Projectile", meta = (ClampMin = 1.f, UIMin = 1.f, Delta = 0.1f))
	float FireRate = 1.f;

private:

	/** Shooting timer */
	UPROPERTY()
	FTimerHandle ShootTimerHandle;

#pragma endregion SHOOT
	
};
