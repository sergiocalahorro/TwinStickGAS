// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Abilities/TSGAbility_Shoot.h"

// Headers - TwinStickGAS
#include "General/BlueprintFunctionLibraries/TSGGameplayStatics.h"
#include "General/Interfaces/TSGShooterInterface.h"
#include "Projectiles/TSGProjectile.h"

#pragma region OVERRIDES

/** Actually activate ability, do not call this directly */
void UTSGAbility_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// Shoot();

	FTimerDelegate ShootTimerDelegate;
	ShootTimerDelegate.BindUFunction(this, FName("Shoot"));
	GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, ShootTimerDelegate, 1.f / FireRate, true, 0.f);
}
	
/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
void UTSGAbility_Shoot::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetWorld()->GetTimerManager().ClearTimer(ShootTimerHandle);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#pragma endregion OVERRIDES

#pragma region SHOOT

/** Shoot projectile */
void UTSGAbility_Shoot::Shoot()
{
	if (AActor* Instigator = GetAvatarActorFromActorInfo())
	{
		const ITSGShooterInterface* ShooterInstigator = CastChecked<ITSGShooterInterface>(Instigator);
		UTSGGameplayStatics::SpawnPoolableObject(Instigator, ProjectileClass, ShooterInstigator->GetShootPointTransform());
	}
}

#pragma endregion SHOOT