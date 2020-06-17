// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::RotateT(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	//if (TurretAudioComponent && (RelativeSpeed >= MinMaxTurnSound || RelativeSpeed <= -MinMaxTurnSound))
	//{
	//	TurretAudioComponent->SetSound(AudioTurret);
	//	TurretAudioComponent->Play();
	//}
	//else 
	//{
	//	TurretAudioComponent->Stop();
	//}

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
