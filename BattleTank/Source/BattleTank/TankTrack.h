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
	void CombineThrottle(float Throttle);
	// Sets a Throttle -1 to +1 (note shows in BP)
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	//Max force per track in Newtons (force = mass (kg)* acceleration (m/s2)), assume no friction to start
	UPROPERTY(EditDefaultsOnly) // effect all tanks
	float TrackMaxDrivingForce = 200000; //(40,000 * 2.682 (0to60 in 10s)) // however things seem slower  // set to 40,000 or 1G of acceleration

private:

	UTankTrack();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
