// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void  UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) // we've set the barrel
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *Barrel->GetComponentLocation().ToString() );
	//UE_LOG(LogTemp, Warning, TEXT("Firing at: %f"), LaunchSpeed); //prove launch speed is making it all the way to the component

	if(!Barrel) {return;} // protect Barrel pointer

	//FVector OutLaunchVelocity; // OUT from the function
	FVector OutLaunchVelocity(0);// initialise to zero to output 0,0,0
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // more accurate than just component
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
			(
				this, //ref to this tankaiming component
				OutLaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed,
				ESuggestProjVelocityTraceOption::DoNotTrace //debug trace // caution don't put ,
			);
	if	(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //outputs the unit vector from FVector
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at: %s"), *GetOwner()->GetName(), *AimDirection.ToString()); 
		// return true; // don't need as not setting a false statement after
		MoveBarrelTowards(AimDirection);
	}
	//if nothing found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//MOve barrel towards an aimdirection by:
	//work out difference between current rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  // gives roll pitch and yaw of barrel //GetForwardVector  =  direction of barrel // Rotation() turn into a struct FRotator, roll pitch Yaw
	auto AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimasRotator: %s"), *AimAsRotator.ToString()); // see what it kicks out
	auto DeltaRotator = AimAsRotator - BarrelRotator; // difference
	
	//move barrel correct amount this frame //Set max elevation speed > create barrel class (SM)

	//given max speed and frame time (framerate independant)
}


