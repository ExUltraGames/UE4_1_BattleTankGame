// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	//could find components and do this in BeginPlay
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InputBinding();
	FindExhaustParticleSystem();
	FindAudioComponent();
	//Tank Drive active under throw
}

void UTankMovementComponent::FindExhaustParticleSystem()
{
	ExhaustSmokeComponent = GetOwner()->FindComponentByClass<UParticleSystemComponent>();// IWYU!!!!
	if (!ensure(ExhaustSmokeComponent)) { return; }
	ExhaustSmokeComponent->DeactivateSystem();
}

void UTankMovementComponent::InputBinding()
{
	InputComponentMovement = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!ensure(InputComponentMovement)) { return; }
	if (InputComponentMovement)
	{
		InputComponentMovement->BindAxis("Move Forward", this, &UTankMovementComponent::IntendMoveForward);
		InputComponentMovement->BindAxis("Turn Right", this, &UTankMovementComponent::IntendTurnRight);
		//UE_LOG(LogTemp, Warning, TEXT("Input Component: %s"), *InputComponentMovement->GetFName().ToString()); // to test
	}
}

void UTankMovementComponent::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	UE_LOG(LogTemp, Warning, TEXT("%s  Audio Component"), *AudioComponent->GetName());
	if (!AudioComponent) { return;}
	AudioComponent->Activate();
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)//float throw -1 to +1 comes from the BindAxis
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	ExhaustActivate(Throw);
	//TankDriveSoundActivate(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::ExhaustActivate(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);
	if (!ExhaustSmokeComponent) { return; }// needed to protect
	if (Throw != 0)
	{
		ExhaustSmokeComponent->Activate();
		//UE_LOG(LogTemp, Warning, TEXT("Exhaust START"));
	}
	else
	{
		ExhaustSmokeComponent->Deactivate();
	}
}

void UTankMovementComponent::TankIdleSoundActivate()
{
	bTankDriveSound = false;
	if (!AudioComponent) { return; }
	if (!bTankIdleSound)
	{
		AudioComponent->Play();
		bTankIdleSound = true;
	}
}

void UTankMovementComponent::TankDriveSoundActivate(float Throw)
{
	bTankDriveSound = false;
	if (!AudioComponent) { return; }
	if (!bTankDriveSound && Throw !=0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DRIVE"));
		AudioComponent->Play(); // play DRIVE here
		bTankDriveSound = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IDLE"));
		//AudioComponent->Play(); // Play DRIVE here
		bTankDriveSound = false;
	}
}