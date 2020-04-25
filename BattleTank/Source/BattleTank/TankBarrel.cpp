// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void  UTankBarrel::Elevate(float DegreesPerSecond)
{
	//move barrel correct amount this frame //Set max elevation speed > create barrel class (SM)

	//given max speed and frame time (framerate independant)
    UE_LOG(LogTemp, Warning, TEXT("BarrelElevateCalled at speed: %f"), DegreesPerSecond);
}