// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

UTankTurret::UTankTurret()
{
	TurretAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Turret"));
	TurretAudioComponent->bAutoActivate = false;
}

void UTankTurret::RotateT(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	if (!TurretAudioComponent) { return; }
	if (TurretAudioComponent && (RelativeSpeed >= MinMaxTurnSound || RelativeSpeed <= -MinMaxTurnSound))
	{
		TurretAudioComponent->Activate();
	}
	else
	{
		TurretAudioComponent->Deactivate(); 
	}

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
