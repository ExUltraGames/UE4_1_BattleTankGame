// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private: // make private as a child class	
	// How close can the AI tank get
	//UPROPERTY(EditAnywhere, Category = Setup)// for testing, change to EditDefaultsOnly once played with
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 8000;
	
private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override; // called when possesed

	UFUNCTION()
	void OnAITankDeath();

	virtual void Tick(float DeltaSeconds) override;
	
};
