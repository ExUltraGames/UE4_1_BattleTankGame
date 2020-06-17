// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	
	void Elevate(float RelativeSpeed, float MinElevationDegrees);

	void BarrelSoundStart(float RelativeSpeed);

	void BarrelSoundStop();

	UPROPERTY()
	UAudioComponent* AudioBarrelComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AudioBarrel = nullptr;
protected:

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float MinMaxElevateSound = 0.3f;

};
