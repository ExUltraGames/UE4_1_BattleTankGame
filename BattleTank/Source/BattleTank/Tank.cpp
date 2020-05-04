// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimingComponent.h"// needed for tankaimingcomponent
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // removed tick as not needed = optimisation
	//adding in constructor // no need to protect pointers added at construction // this will put in Tank.bp // so we can SET Barrel & Turret
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")); // removed in refactor
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component")); Removed and made spanwable instead
}

// removed this to aimingcompoent and called in BP

// void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)//change UStaticMeshComponent
// {
// 	TankAimingComponent->SetBarrelReference(BarrelToSet);
// 	Barrel = BarrelToSet; // keeping a local reference
// }

// void ATank::SetTurretReference(UTankTurret* TurretToSet)//change UStaticMeshComponent
// {
// 	TankAimingComponent->SetTurretReference(TurretToSet);
// }

// Called when the game starts or when spawned // not used remove
// void ATank::BeginPlay()
// {
// 	Super::BeginPlay();
// }

// Called to bind functionality to input // not used
// void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }

void ATank::AimAt(FVector HitLocation)
{
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *GetName(), *HitLocation.ToString()); // moved to aiming component
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank Fires"), GetWorld()->GetTimeSeconds());

	bool isReloaded = (FPlatformTime::Seconds() - LastFiretime) > ReloadTimeInSeconds;
	//if(!Barrel) {return;} cahnge and move method into
	if(Barrel && isReloaded)
	{
		//spawn projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, // class to spawn
			Barrel->GetSocketLocation(FName("Projectile")), // location to spawn
			Barrel->GetSocketRotation(FName("Projectile")) // rotation to spawn
		); // use signauture number 2 for this?
		
		if(!Projectile) {return;} // I am  leaving in for protection but not needed
		
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiretime = FPlatformTime::Seconds();
	}
	
}



