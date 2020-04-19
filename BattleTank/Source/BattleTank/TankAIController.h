// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h" // for ATank
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override; //checks in hieracy for beginplay
	ATank* GetControlledTank() const; // pointer to an AITank
	ATank* GetPlayerTank() const; // returns pointer to player tank

	
};
