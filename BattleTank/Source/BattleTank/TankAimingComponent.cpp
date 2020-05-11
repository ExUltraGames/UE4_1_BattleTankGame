// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()// so we can log out
{
	//so that first fire is after initial reload
	LastFiretime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto LastTimeFireGap = (FPlatformTime::Seconds() - LastFiretime);
	if ( LastTimeFireGap < ReloadTimeInSeconds )// can use GetWorld()->GetTimeSeconds()
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

bool  UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) {return false;} // protect // note 
	auto BarrelForward = Barrel->GetForwardVector();
	
	return !BarrelForward.Equals(AimDirection, 0.01);//vectors are equal using FVector::Equals method
}

void UTankAimingComponent::AimAt(FVector HitLocation) // float LaunchSpeed no longer need to be passed in due to refactor
{

	if(!ensure(Barrel)) {return;}

	FVector OutLaunchVelocity;// initialise to zero to output 0,0,0
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // more accurate than just component
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
			( // DEBUG - NEED ALL PARAMETERS EVEN THE DEFAULT ONES // ADD FALSE, 0,0 BACK IN & ESuggestProjVelocityTraceOption::DoNotTrace
				this, //ref to this tankaiming component
				OutLaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed,
				false, //debug
				0,//debug
				0,//debug
				ESuggestProjVelocityTraceOption::DoNotTrace //debug trace // caution don't put , at end
			);
	if	(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal(); //change from local to member variable, see .h
		//UE_LOG(LogTemp, Warning, TEXT("%s aimdirection is: %s"), *GetOwner()->GetName(), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure (Turret || Barrel)) {return;}

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  // gives roll pitch and yaw of barrel //GetForwardVector  =  direction of barrel // Rotation() turn into a struct FRotator, roll pitch Yaw
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator; // difference
	
	Barrel->Elevate(DeltaRotator.Pitch); // removed magic number
	Turret->RotateT(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if(FiringState != EFiringState::Reloading)
	{
		//spawn projectile
			if(!ensure(Barrel)) {return;} // move to where need and spilt for more info
			if(!ensure(ProjectileBlueprint)) {return;}
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