// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    // auto Time = GetWorld()->GetTimeSeconds();
    // auto Name = GetName(); // local name i.e. track // GetOwner()->GetName() gives name of Owner i.e. Tank
    //Throttle = FMath::Clamp<float>(Throttle, -1, +1);
	//UE_LOG(LogTemp, Warning, TEXT("%s Throttle %f"), *GetOwner()->GetName(), Throttle);

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation(); // location of track
    //auto TankRoot = GetOwner()->GetRootComponent(); // this GetRootComponent (a USceneComponent) doesn't allow force so cast it to one that does // see hieracy
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());// add force to route component (tank)//TankRoot is now a UPrimitiveComponent the lowest level we can aply a force to
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}