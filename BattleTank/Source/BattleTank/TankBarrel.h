// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent), hideCategories = ("Colision")) 
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Between -1 & +1
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20; // sensible default  

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40; // sensible default  // find in BP and set in cpp

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0; // sensible default  
};