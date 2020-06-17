// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// -1 is max downward speed, and +1 is max up movement
	void RotateT(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AudioTurret = nullptr;
	
protected:

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 25;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float MinMaxTurnSound = 0.3f;
};
