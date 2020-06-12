// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

UTankBarrel::UTankBarrel()
{
	BarrelAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Barrel"));
	BarrelAudioComponent->bAutoActivate = false;
}

void UTankBarrel::Elevate(float RelativeSpeed, float MinElevationDegrees)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	//To Do add in a slight delay?
	if (!BarrelAudioComponent) { return; }
	if (BarrelAudioComponent && (RelativeSpeed >= MinMaxElevateSound || RelativeSpeed <= -MinMaxElevateSound))
	{
		BarrelAudioComponent->Activate();
		//BarrelAudioComponent->SetSound(BarrelAudio);
	}
	else
	{
		BarrelAudioComponent->Deactivate();
	}

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
