// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h" // so know methods

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) // similar to aimingcomponent
{
    //if(!LeftTrackToSet || !RightTrackToSet) {return;} // not needed as would get set to nullptr whan passed in
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
     //no need to call super as we are replacing the functioanlity we want the MoveVelocity Vector
     auto TankName = GetOwner()->GetName();
     auto MoveVelocityString = MoveVelocity.ToString();
     UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
   	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), Throw);

    // access tracks to move
    if(!LeftTrack || !RightTrack) {return;} // needed to protect // i.e. they exist
    LeftTrack->SetThrottle(Throw); //IWYU
    RightTrack->SetThrottle(Throw);
    //TODO prevent double speed from dual control use //TODO clamp throttle vale so player can't alter

}

void UTankMovementComponent::IntendTurnRight(float Throw) // called this to say what a +value does, not just called turn
{
    if(!LeftTrack || !RightTrack) {return;}
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
    //TODO prevent double speed from dual control use //TODO clamp throttle vale so player can't alter

}
 // could do this but have assigned a -1 to A key in binding to turn left instead // naming of above is to show what a +value does
// void UTankMovementComponent::IntendTurnLeft(float Throw)
// {
//     LeftTrack->SetThrottle(-Throw);
//     RightTrack->SetThrottle(Throw);
// }