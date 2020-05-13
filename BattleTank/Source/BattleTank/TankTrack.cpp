// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //UE_LOG(LogTemp, Warning, TEXT("Tick"));

    //Calculate required acceleration this frame to correct
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    //Calc and apply sideways (f=ma)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
    TankRoot->AddForce(CorrectionForce);
}

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