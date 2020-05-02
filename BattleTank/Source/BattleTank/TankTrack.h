// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//the comment block below is text that shows on hover in BP
/**
 TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public: 
	// Sets a Throttle -1 to +1 (note shows in BP)
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
};
