// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move barrel correct amount this frame //Set max elevation speed > create barrel class (SM)
	//given max speed and frame time (framerate independant)
    //UE_LOG(LogTemp, Warning, TEXT("%f BarrelElevateCalled at speed: %f"),GetWorld()->GetTimeSeconds(), RelativeSpeed); // add time to show log happening every tick
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1); // clamps relative speed to -1 +1
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // 0to1 * Maxpersec * Delta = same speed across devices
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; // need to clamp // new elevation taking into account current elevation
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
