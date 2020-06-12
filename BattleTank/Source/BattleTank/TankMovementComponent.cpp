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
}

void UTankMovementComponent::FindExhaustParticleSystem()
{
	ExhaustSmokeComponent = GetOwner()->FindComponentByClass<UParticleSystemComponent>();// IWYU!!!!
	if (!ensure(ExhaustSmokeComponent)) { return; }
	ExhaustSmokeComponent->DeactivateSystem();
}

void UTankMovementComponent::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent) { return;}
	AudioComponent->Activate();
}

void UTankMovementComponent::InputBinding()
{
	InputComponentMovement = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!ensure(InputComponentMovement)) { return; }
	if (InputComponentMovement)
	{
		InputComponentMovement->BindAxis("Move Forward", this, &UTankMovementComponent::IntendDrive);
		InputComponentMovement->BindAxis("Turn Right", this, &UTankMovementComponent::IntendTurn);
		//UE_LOG(LogTemp, Warning, TEXT("Input Component: %s"), *InputComponentMovement->GetFName().ToString()); // to test
		InputComponentMovement->BindAction("DriveSound", IE_Pressed, this, &UTankMovementComponent::TankDriveSoundActivate);
		InputComponentMovement->BindAction("DriveSound", IE_Released, this, &UTankMovementComponent::TankIdleSoundActivate);
	}
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

	TankDriveSounds();
}

void UTankMovementComponent::IntendDrive(float Throw)
{
	IntendMoveForward(Throw);
	ExhaustActivate();
	//TankDriveSounds(); //doesn't work for non-ai tank // use key binding???? // order of compile??
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	IntendTurnRight(Throw);
	ExhaustActivate();
	//TankDriveSounds(); //doesn't work for non-ai tank // use key binding???? // order of compile??
}

void UTankMovementComponent::IntendMoveForward(float Throw)//float throw -1 to +1 comes from the BindAxis
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	Drive = Throw;
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	Turn = Throw;
}

void UTankMovementComponent::ExhaustActivate()
{
	if (!ExhaustSmokeComponent) { return; }
	if (Drive != 0 || Turn != 0)
	{
		ExhaustSmokeComponent->Activate();
	}
	else
	{
		ExhaustSmokeComponent->Deactivate();
	}
}

void UTankMovementComponent::TankDriveSounds()
{
	if (Drive != 0 || Turn != 0)
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(AudioDrive);
		AudioComponent->Play();
	}
	else
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(AudioIdle);
		AudioComponent->Play();
	}
}

void UTankMovementComponent::TankDriveSoundActivate()
{
	if (!AudioComponent) { return; }
	AudioComponent->Stop();
	AudioComponent->SetSound(AudioDrive);
	AudioComponent->Play();
}
void UTankMovementComponent::TankIdleSoundActivate()
{
	if (!AudioComponent) { return; }
	AudioComponent->Stop();
	AudioComponent->SetSound(AudioIdle);
	AudioComponent->Play();
}
