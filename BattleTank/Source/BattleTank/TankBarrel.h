// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankBarrel();

	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed, float MinElevationDegrees);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* BarrelAudioComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float MinMaxElevateSound = 0.3f;

};
