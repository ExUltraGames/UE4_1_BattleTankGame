// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//SetActorEnableCollision(true);
}

//leave in as this is how apply to actor
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();
//	OnActorHit.AddDynamic(this, &ATank::OnHit);
//	//OnComponentHit.AddDynamic(this, &ATank::OnHit); // TODO simulate Generates hit events enable // SetActorEnableCollision(true);
//}
//
//void ATank::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
//{	
//	ApplyDownForce();
//}
//
//
//void ATank::ApplyDownForce()
//{	
//	
//	auto FlySpeed = FVector::DotProduct(GetActorUpVector(), GetVelocity());
//	UE_LOG(LogTemp, Warning, TEXT("FlySpeed: %f"), FlySpeed);
//	// Work-out the required acceleration this frame to correct
//	auto DeltaTime = GetWorld()->GetDeltaSeconds(); // get it when need it and don't need to pass in
//	auto CorrectionAcceleration = -FlySpeed / DeltaTime * GetActorUpVector();
//
//	// Calculate and apply sideways (F = m a)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // TODO change to TANK not Root ? GetOwner?
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration); 
//	TankRoot->AddForce(CorrectionForce);
//}