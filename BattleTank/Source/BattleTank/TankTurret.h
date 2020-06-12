// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTurret();
	// -1 is max downward speed, and +1 is max up movement
	void RotateT(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 25;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* TurretAudioComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float MinMaxTurnSound = 0.3f;
};
