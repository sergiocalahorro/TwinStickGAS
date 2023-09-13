// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/TSGProjectile.h"

// Headers - Unreal Engine
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Headers - TwinStickGAS
#include "Core/PoolableComponent.h"
#include "Projectiles/TSGProjectileData.h"

#pragma region INITIALIZATION

/** Sets default values for this actor's properties */
ATSGProjectile::ATSGProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetEnableGravity(false);
	SphereComponent->SetSimulatePhysics(false);
	RootComponent = SphereComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	
	PoolableComponent = CreateDefaultSubobject<UPoolableComponent>(TEXT("PoolableComponent"));
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

#if WITH_EDITOR
/** Called when a property on this object has been modified externally */
void ATSGProjectile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATSGProjectile, ProjectileData))
	{
		InitializeProjectile();
	}
}
#endif

/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized, only called during gameplay */
void ATSGProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddUniqueDynamic(this, &ATSGProjectile::OnHit);

	PoolableComponent->EnabledDelegate.AddUniqueDynamic(this, &ATSGProjectile::OnEnabled);
	PoolableComponent->DisabledDelegate.AddUniqueDynamic(this, &ATSGProjectile::OnDisabled);
}

/** Called when the game starts or when spawned */
void ATSGProjectile::BeginPlay()
{
	Super::BeginPlay();

	InitializeProjectile();
}

#pragma endregion OVERRIDES

#pragma region PROJECTILE

/** Initialize projectile's values */
void ATSGProjectile::InitializeProjectile() const
{
	StaticMeshComponent->SetStaticMesh(ProjectileData->StaticMesh);
	
	ProjectileMovementComponent->InitialSpeed = ProjectileData->InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileData->MaxSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileData->GravityScale;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = ProjectileData->bInitialVelocityInLocalSpace;
	ProjectileMovementComponent->bRotationFollowsVelocity = ProjectileData->bRotationFollowsVelocity;
	ProjectileMovementComponent->bShouldBounce = ProjectileData->bShouldBounce;
	ProjectileMovementComponent->Bounciness = ProjectileData->Bounciness;
}

/** Handle projectile's hit */
void ATSGProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	PoolableComponent->Disable();
}

/** Handle projectile enabled */
void ATSGProjectile::OnEnabled()
{
	ProjectileMovementComponent->Activate(true);
	ProjectileMovementComponent->Velocity = GetActorRotation().Vector() * ProjectileMovementComponent->InitialSpeed;
}

/** Handle projectile disabled */
void ATSGProjectile::OnDisabled()
{
	ProjectileMovementComponent->Deactivate();
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;

	if (!ProjectileData)
	{
		return;
	}
	
	if (ProjectileData->ImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileData->ImpactParticles, GetActorTransform());
	}

	if (ProjectileData->ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ProjectileData->ImpactSound, GetActorLocation());
	}
}

#pragma endregion PROJECTILE
