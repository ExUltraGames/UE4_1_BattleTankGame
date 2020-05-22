// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{	// only get force when tracks on the ground
	DriveTrack();
	ApplySideWaysForce();
	CurrentThrottle = 0; // need to reset so stops applying

}

void UTankTrack::ApplySideWaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds(); // get it when need it and don't need to pass in
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1); // clamp throttle to +1-1 <float> = float out
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	ApplyDownForce();

}

void UTankTrack::ApplyDownForce()
{
	float FlySpeed = FVector::DotProduct(GetUpVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds(); // get it when need it and don't need to pass in
	auto CorrectionAcceleration = -FlySpeed / DeltaTime * GetUpVector();

	//UE_LOG(LogTemp, Warning, TEXT("CorrectionAccleration: %s"), *CorrectionAcceleration.ToString());
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 4;
	//UE_LOG(LogTemp, Warning, TEXT("TankRoot: %s CorrectionForce: %s"), *TankRoot->GetName(), *CorrectionForce.ToString());
	TankRoot->AddForce(CorrectionForce);
}