// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h" // for #include for aiming pointer in protected / / forward declaration - UTankAimingComponent // move to #include to cpp
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarations
class UTankBarrel; // forward declaration
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: //as this is external worldview of tank
	void AimAt(FVector HitLocation);//included in TankPlayerController so can use there & in TankAIController
	
	UFUNCTION(BlueprintCallable, Category = Setup) // a method we can call from blueprint
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup) // a method we can call from blueprint
	void SetTurretReference(UTankTurret* TurretToSet);

protected: // need to access using UPROPERTY // but doens't need to be outside Tank
	 UTankAimingComponent* TankAimingComponent = nullptr;// creating pointer to aiming component , need the component to be made in c++ tankaimingcomponent

private://
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Editanywhere, Category = Firing)
	float LaunchSpeed = 100000; //= 1000m/s = todo find a sensible default value for tweaking in BP

};
