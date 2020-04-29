// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) ) // needed to compile whole TankBattle
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Between -1 & +1
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 8; // sensible default  

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 60; // sensible default  // find in BP and set in cpp

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0; // sensible default  
};