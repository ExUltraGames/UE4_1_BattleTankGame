// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Sound/SoundBase.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LaunchProjectile(float Speed);

private:

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr; // 	#include "PhysicsEngine/RadialForceComponent.h"

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void OnTimerExpire();


	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DestroyDelay = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ProjectileDamage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ImpactBlastSFX = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* LaunchBlastSFX = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* WhistleSFX = nullptr;


	void ImpactBlastActivate();
	void WhistleActivate();
};
