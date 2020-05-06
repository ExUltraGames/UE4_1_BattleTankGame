// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h" // for ATank // forward declare
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be last include

class ATank;
class UTankAimingComponent;
/**
 * Responsible for helping the player aim.
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController // atankplayercontroller is based on APLayerController
{
	GENERATED_BODY()
	
public:

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank* GetControlledTank() const; // pointer to a Tank

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)// don't need implementation with this macro // wire up in BP
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);// forward declare

private:
	virtual void BeginPlay() override; //checks in hieracy for beginplay
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrossHair(); // start tank moving barrel

	//return OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const; // out parameters make a reference to use / look for &
	
	UPROPERTY(EditDefaultsOnly) // set these to editanywhere // if move pixel in BP, would need to change these values
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const; // refactor
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

};
