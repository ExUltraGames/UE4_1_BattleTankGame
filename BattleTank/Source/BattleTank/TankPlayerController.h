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
	ATank* GetControlledTank() const; // pointer to a Tank
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override; //checks in hieracy for beginplay

private:
	void AimTowardsCrossHair(); // start tank moving barrel 
};
