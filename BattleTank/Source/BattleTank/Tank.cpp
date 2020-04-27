// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimingComponent.h"// needed for tankaimingcomponent
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // removed tick as not needed = optimisation
	//adding in constructor // no need to protect pointers added at construction // this will put in Tank.bp // so we can SET Barrel & Turret
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)//change UStaticMeshComponent
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet; // keeping a local reference
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)//change UStaticMeshComponent
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *GetName(), *HitLocation.ToString()); // moved to aiming component
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank Fires"), GetWorld()->GetTimeSeconds());

	if(!Barrel) {return;}
	//spawn projectile
	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint, // class to spawn
		Barrel->GetSocketLocation(FName("Projectile")), // location to spawn
		Barrel->GetSocketRotation(FName("Projectile")) // rotation to spawn
	); // use signauture number 2 for this?

}

