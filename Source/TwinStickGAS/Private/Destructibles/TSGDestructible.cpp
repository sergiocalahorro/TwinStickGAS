// Fill out your copyright notice in the Description page of Project Settings.

#include "Destructibles/TSGDestructible.h"

// Headers - TwinStickGAS
#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"
#include "Components/TSGHealthComponent.h"

#pragma region INITIALIZATION

/** Sets default values for this actor's properties */
ATSGDestructible::ATSGDestructible()
{
	PrimaryActorTick.bCanEverTick = false;

	// Static mesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	// Ability system
	AbilitySystemComponent = CreateDefaultSubobject<UTSGAbilitySystemComponent>(TEXT("AbilitySytemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	// Health
	HealthComponent = CreateDefaultSubobject<UTSGHealthComponent>(TEXT("HealthComponent"));
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized */
void ATSGDestructible::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
	HealthComponent->HealthChangedDelegate.AddUniqueDynamic(this, &ATSGDestructible::OnHealthChanged);
}

/** Called when the game starts */
void ATSGDestructible::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion OVERRIDES

#pragma region GAS

/** Get AbilitySystemComponent */
UAbilitySystemComponent* ATSGDestructible::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

#pragma endregion GAS

#pragma region HEALTH

/** Handle health changed */
void ATSGDestructible::OnHealthChanged(UTSGHealthComponent* TSGHealthComponent, float OldValue, float NewValue, AActor* EffectInstigator)
{
	UE_LOG(LogTemp, Warning, TEXT("ATSGDestructible::OnHealthChanged - %s | CurrentHealth: %f | EffectInstigator: %s"), *GetNameSafe(this), NewValue, *GetNameSafe(EffectInstigator));
}

#pragma endregion HEALTH
