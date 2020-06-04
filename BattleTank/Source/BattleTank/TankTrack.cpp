// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//void UTankTrack::BeginPlay()
//{
	//Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
//}

//void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
// not needed
//}


//No Longer needed as applying force to wheels with physics constarints
//void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{	// only get force when tracks on the ground
	// ApplySideWaysForce();
	// CurrentThrottle = 0; // needed for Applysideways force  to reset so stops applying
//}

// no longer needed as using physics constraints
//void UTankTrack::ApplySideWaysForce()
//{
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//
//	// Work-out the required acceleration this frame to correct
//	auto DeltaTime = GetWorld()->GetDeltaSeconds(); // get it when need it and don't need to pass in
//	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
//
//	// Calculate and apply sideways (F = m a)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
//	TankRoot->AddForce(CorrectionForce);
//}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1); // remove as member variable and set as an argument for drive track
	DriveTrack(CurrentThrottle);// drive when throttle applied
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray; // construct it
	TArray<USceneComponent*> Children; // construct it
	GetChildrenComponents(true, Children); // get all children of type USceneComponent
	for (USceneComponent* Child : Children) // iterate over the Usecenecomponents // Get back USceneComponent* Child, by iterating over Children
	{	//Get the spawnpoint
		auto SpawnPointChild = Cast<USpawnPoint>(Child);//cast to spawnpoint // the thing we want out all children
		if (!SpawnPointChild) continue; // early continue as a for loop, don't use early return
		//Get the Actor it spawns
		AActor* SpawnChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnChild);
		if (!SprungWheel) continue;

		//this is to ensure we get a sprungwheel Actor of type sprungwheel for our Array // check, cast to make sure we get what we want

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}
//not needed as applying physics constraints
//void UTankTrack::ApplyDownForce()
//{
//	float FlySpeed = FVector::DotProduct(GetUpVector(), GetComponentVelocity());
//	auto DeltaTime = GetWorld()->GetDeltaSeconds(); // get it when need it and don't need to pass in
//	auto CorrectionAcceleration = -FlySpeed / DeltaTime * GetUpVector();
//
//	//UE_LOG(LogTemp, Warning, TEXT("CorrectionAccleration: %s"), *CorrectionAcceleration.ToString());
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 4;
//	//UE_LOG(LogTemp, Warning, TEXT("TankRoot: %s CorrectionForce: %s"), *TankRoot->GetName(), *CorrectionForce.ToString());
//	TankRoot->AddForce(CorrectionForce);
//}