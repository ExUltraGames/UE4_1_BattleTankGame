// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;// forward declaration // define more than one class

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	// Todo add SetTurretReference
	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	//UStaticMeshComponent* Barrel = nullptr; // needs changing as now a Tank Barrel SM Component
	UTankBarrel* Barrel = nullptr; // needs forward declaration // don't include TankBarrel.h in anothe .h file only .cpp = compile error

	void MoveBarrelTowards(FVector AimDirection); // nothing outside tankaiming component needs to move barrel = private
		
};
