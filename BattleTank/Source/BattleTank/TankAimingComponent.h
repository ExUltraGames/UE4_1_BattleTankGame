// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM() // declare
enum class EFiringState : uint8 // type of enum
{
	Reloading,
	Aiming,
	Locked
};

// forward declaration // define more than one class
class UTankBarrel;
class UTankTurret;

//Holds Barrel's Properties and Elevate method // anotation will come in hover over if above
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation);// aimat doesn't need launchspeed from Tank anymore, as below, removed

protected: // access from subclass the TankAimingComponent
	UPROPERTY(BlueprintReadOnly, Category = State_Running)
	EFiringState FiringState = EFiringState::Aiming; // Declare and initialise

private:
	UTankAimingComponent(); // moved in refactor
	
	UTankBarrel* Barrel = nullptr; // needs forward declaration // don't include TankBarrel.h in anothe .h file only .cpp = compile error
	void MoveBarrelTowards(FVector AimDirection); // nothing outside tankaiming component needs to move barrel = private
	
	UTankTurret* Turret = nullptr;
	void MoveTurretTowards(FVector AimDirection);
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000; //= 1000m/s = todo find a sensible default value for tweaking in BP
};
