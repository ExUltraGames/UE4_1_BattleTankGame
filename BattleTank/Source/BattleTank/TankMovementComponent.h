// Copyright EmbraceIT Ltd.

#pragma once

#include "Components/AudioComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/NavMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	void IntendDrive(float Throw);
	void IntendTurn(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	virtual void BeginPlay() override;
private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	void InputBinding();
	void FindExhaustParticleSystem();
	void ExhaustActivate();

	UPROPERTY()
	UInputComponent* InputComponentMovement = nullptr;
	UPROPERTY()
	UParticleSystemComponent* ExhaustSmokeComponent = nullptr;//IWYU
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AudioIdle = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AudioDrive = nullptr;
	
	UPROPERTY()
	UAudioComponent* MovementAudioComponent = nullptr;

	void TankIdleSoundActivate();
	void TankDriveSoundActivate();
	void TankDriveSounds();
	float Drive;
	float Turn;
};
