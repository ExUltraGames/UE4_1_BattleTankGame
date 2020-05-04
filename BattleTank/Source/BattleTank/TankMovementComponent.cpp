// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h" // so know methods

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) // similar to aimingcomponent
{
    if(!LeftTrackToSet || !RightTrackToSet) {return;}
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
   	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), Throw);

    // access tracks to move
    LeftTrack->SetThrottle(Throw); //IWYU
    RightTrack->SetThrottle(Throw);

    //TODO prevent double speed from dual control use

}