// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	//ProjectileBlueprint->ClassDefaultObject;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So that first first is after initial reload
	LastFireTime = FPlatformTime::Seconds();
	
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0) // ensure even if go -ve for any reason
	{
		FiringState = EFiringState::OutofAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

// returns FiringState for use in AIController
EFiringState UTankAimingComponent::GetFiringState() const // const so can't change
{
	return FiringState;
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equal
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimInDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimInDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	float Elevation = Turret->RelativeRotation.Yaw;
	if (Elevation <= FrontFiringDegreeRange && Elevation >= -FrontFiringDegreeRange)
	{
		Barrel->Elevate(DeltaRotator.Pitch, BarrelMinElevationFront);
	}
	else 
	{
		Barrel->Elevate(DeltaRotator.Pitch, BarrelMinElevation);
	}
	// always Yaw shortest route
	
	if (FMath::Abs(DeltaRotator.Yaw) < 180)//absolute value +or-
	{
		Turret->RotateT(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateT(-DeltaRotator.Yaw);
	}

	//TODO if Turret RelativeRotation.Yaw is -12 to 12 degress set Barrel MinElevationDegrees = -10
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return;  }
		
		// example how to use this type of thing FActorSpawnParameters // this caused only 1 projectile to be allowed in scene
		//FActorSpawnParameters NewParams = FActorSpawnParameters();
		//NewParams.Name = (FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			//NewParams
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}


