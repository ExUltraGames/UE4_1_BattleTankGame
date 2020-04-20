// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h" // for ATank
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController // atankplayercontroller is based on APLayerController
{
	GENERATED_BODY()
	
public:

private:
	ATank* GetControlledTank() const; // pointer to a Tank
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override; //checks in hieracy for beginplay
	void AimTowardsCrossHair(); // start tank moving barrel

	//return OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const; // out parameters make a reference to use / look for &
	UPROPERTY(EditAnywhere) // set these to editanywhere // if move pixel in BP, would need to change these values
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const; // refactor

};
