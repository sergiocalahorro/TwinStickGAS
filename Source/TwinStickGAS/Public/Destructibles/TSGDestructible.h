// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"

#include "TSGDestructible.generated.h"

// Forward declarations - TwinStickGAS
class UTSGHealthComponent;
class UTSGAbilitySystemComponent;

UCLASS()
class TWINSTICKGAS_API ATSGDestructible : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:
	
	/** Sets default values for this actor's properties */
	ATSGDestructible();

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

protected:

	/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized */
	virtual void PostInitializeComponents() override;
	
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region GAS

public:

	/** Get AbilitySystemComponent */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:

	/** Static mesh component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	/** Ability system component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGAbilitySystemComponent> AbilitySystemComponent;

	/** Health component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGHealthComponent> HealthComponent;

#pragma endregion GAS

#pragma region HEALTH

private:

	/** Handle health changed */
	UFUNCTION()
	void OnHealthChanged(UTSGHealthComponent* TSGHealthComponent, float OldValue, float NewValue, AActor* EffectInstigator);

#pragma endregion HEALTH

};
