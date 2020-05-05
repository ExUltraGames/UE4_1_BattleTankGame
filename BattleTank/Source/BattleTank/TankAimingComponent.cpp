// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // TODO
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if(!Barrel) {return;}

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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //outputs the unit vector from FVector
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Found"),GetWorld()->GetTimeSeconds());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!Turret || !Barrel) {return;}

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  // gives roll pitch and yaw of barrel //GetForwardVector  =  direction of barrel // Rotation() turn into a struct FRotator, roll pitch Yaw
	auto AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimasRotator: %s"), *AimAsRotator.ToString()); // see what it kicks out
	auto DeltaRotator = AimAsRotator - BarrelRotator; // difference
	
	Barrel->Elevate(DeltaRotator.Pitch); // removed magic number
	Turret->RotateT(DeltaRotator.Yaw);
}