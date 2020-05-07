// Copyright theZombieroom

#pragma once

//#include "TankAimingComponent.h" // for #include for aiming pointer in protected / / forward declaration - UTankAimingComponent // move to #include to cpp
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarations
class UTankBarrel; // forward declaration
class UTankTurret;
class UTankAimingComponent;
class AProjectile; // needed for TSubclassOf// make it available

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public: //as this is external worldview of tank
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = Firing) // a method we can call from blueprint with Launchspeed see below
	void Fire(); 

	void AimAt(FVector HitLocation);//included in TankPlayerController so can use there & in TankAIController



protected: // need to access using UPROPERTY // but doens't need to be outside Tank
	UPROPERTY(BlueprintReadOnly) // for UI Widget
	UTankAimingComponent* TankAimingComponent = nullptr;// creating pointer to aiming component , need the component to be made in c++ tankaimingcomponent
	
private://
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditDefaultsOnly, Category = Setup) // set of every instance of Tank
	//UClass* ProjectileBlueprint; // or can TSubclassOf<UProjectileBlueprint> ProjectileBlueprint; as this enforces a choice, smaller selection
	TSubclassOf<AProjectile> ProjectileBlueprint; // Projectile blueprint based on projectile.h class which is an Actor

	//TODO remove once firing is moved to AimingComponent // leave copy
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000; //= 1000m/s = todo find a sensible default value for tweaking in BP

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	//Local barrel referecne for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO remove

	double LastFiretime = 0; //Initilaise at 0
};
