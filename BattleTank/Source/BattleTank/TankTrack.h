// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//Forward Declare
class ASprungWheel; //IWYU in cpp

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // Assume 40 tonne tank, and 1g accelleration

private:
	UTankTrack();

	//virtual void BeginPlay() override;

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Get the Wheels = return a TArray of class pointers
	TArray<ASprungWheel*> GetWheels() const; // how iterate over child components

	//void ApplySideWaysForce();

	void DriveTrack(float CurrentThrottle);// remove as member variable and set as an argument for drive track

	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//void ApplyDownForce();

	//UFUNCTION()
	//void GetReversedHit(const FHitResult& Hit);
};
