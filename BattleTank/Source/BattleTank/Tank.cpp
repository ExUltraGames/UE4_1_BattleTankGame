// Copyright theZombieroom

#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // removed tick as not needed = optimisation
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
{
	if(!ensure(Barrel)) {return;}
	bool isReloaded = (FPlatformTime::Seconds() - LastFiretime) > ReloadTimeInSeconds;
	
	if(isReloaded)
	{
		//spawn projectile
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, // class to spawn
			Barrel->GetSocketLocation(FName("Projectile")), // location to spawn
			Barrel->GetSocketRotation(FName("Projectile")) // rotation to spawn
		); 
		
		if(!ensure(Projectile)) {return;} 		
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiretime = FPlatformTime::Seconds();
	}
}



