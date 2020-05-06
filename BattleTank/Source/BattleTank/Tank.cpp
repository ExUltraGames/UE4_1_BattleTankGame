// Copyright theZombieroom

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
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: %s Constructor Called"), *GetName());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: %s BeginPlay Called"), *GetName());
}

void ATank::AimAt(FVector HitLocation)
{
		if(!ensure(TankAimingComponent)) {return;}
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed); // this is the cause of crash, needs protecting
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



