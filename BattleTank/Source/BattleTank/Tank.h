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
class UTankMovementComponent;
class AProjectile; // needed for TSubclassOf// make it available

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: //as this is external worldview of tank
	
	UFUNCTION(BlueprintCallable, Category = Setup) // a method we can call from blueprint
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup) // a method we can call from blueprint
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing) // a method we can call from blueprint with Launchspeed see below
	void Fire(); // need to implement

	void AimAt(FVector HitLocation);//included in TankPlayerController so can use there & in TankAIController


protected: // need to access using UPROPERTY // but doens't need to be outside Tank
	UTankAimingComponent* TankAimingComponent = nullptr;// creating pointer to aiming component , need the component to be made in c++ tankaimingcomponent
	
	UPROPERTY(BlueprintReadOnly)// makes c++ property readable in BP so we can assign
	UTankMovementComponent* TankMovementComponent = nullptr;// creating private variable to store pointer to movement component

private://
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup) // set of every instance of Tank
	//UClass* ProjectileBlueprint; // or can TSubclassOf<UProjectileBlueprint> ProjectileBlueprint; // this enforces a choice?
	TSubclassOf<AProjectile> ProjectileBlueprint; // Projectile blueprint based on projectile.h class whihc is an Actor

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000; //= 1000m/s = todo find a sensible default value for tweaking in BP

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	//Local barrel referecne for spawning projectile
	UTankBarrel* Barrel = nullptr; // set in cpp

	double LastFiretime = 0; //Initilaise at 0
};
