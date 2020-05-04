// Copyright theZombieroom

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 For Driving TankTracks
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// public as called by BP
	UFUNCTION(BlueprintCallable, Category = Setup) // can use quotes "Setup"
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw); // take in float will receive -1 to +1 // throw of joystick
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);
	// UFUNCTION(BlueprintCallable, Category = Input)
	// void IntendTurnLeft(float Throw);


private:
	//Called from pathfinding logic by AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override; // override here // taken from "GameFramework/NavMovementComponent.h" 
	UTankTrack* LeftTrack = nullptr; //protects and gives a known address for pointers // don't forget *
	UTankTrack* RightTrack = nullptr; // needed as used in several references across class
};
