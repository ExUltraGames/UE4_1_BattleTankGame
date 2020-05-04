//Copyright theZombieroom


#include "TankMovementComponent.h"
#include "TankTrack.h" // so know methods

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) // similar to aimingcomponent
{
    //if(!LeftTrackToSet || !RightTrackToSet) {return;} // not needed as would get set to nullptr whan passed in
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{   // AI only
    //no need to call super as we are replacing the functioanlity we want the MoveVelocity Vector
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // unit vector of tank facing forward (tanks local X axis, with length of 1)
    auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // unit vector in direction tank wants to move
         
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention); // gives float
    IntendMoveForward(ForwardThrow); // send to 
     
    auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z; // gives vector so need the Z component
    IntendTurnRight(TurnThrow);
    
    //UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), TurnThrow, ForwardThrow); //prove -1 to +1
   
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
   	// access tracks to move
    if(!LeftTrack || !RightTrack) {return;} // needed to protect // i.e. they exist
    LeftTrack->SetThrottle(Throw); //IWYU
    RightTrack->SetThrottle(Throw);
    //UE_LOG(LogTemp, Warning, TEXT("Throw %f"), Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) // called this to say what a +value does, not just called turn
{
    if(!LeftTrack || !RightTrack) {return;}
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
// could do this but have simply assigned a -1 to A key in binding to turn left instead // naming of above is to show what a +value does
// void UTankMovementComponent::IntendTurnLeft(float Throw)
// {
//     LeftTrack->SetThrottle(-Throw);
//     RightTrack->SetThrottle(Throw);
// }