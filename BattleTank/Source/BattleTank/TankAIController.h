// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h" // for ATank // moved to cpp and forward declare
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

private:
	virtual void BeginPlay() override; //checks in hieracy for beginplay
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000; //assume cm for now = 30m away 
};
