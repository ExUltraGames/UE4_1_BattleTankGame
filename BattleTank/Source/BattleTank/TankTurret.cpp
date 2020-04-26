// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateT(float RelativeSpeed)
{
    // move turret at correct speed per frame

    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // 0to1 * Maxpersec * Delta = same speed across devices
	auto NewRotation = RelativeRotation.Yaw + RotationChange; // need to clamp // new elevation taking into account current elevation
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}