// Copyright EmbraceIT Ltd.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutofAmmo
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	// for AIController
	EFiringState GetFiringState() const; // const so can't change

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void ReloadSound();
	
	void BarrelSoundStart(float RelativeSpeed);

	void TurretSoundStart(float RelativeSpeed);

	float RelativeBarrelSpeed;
	float RelativeTurretSpeed;

	virtual void BeginPlay() override;

	void FindBarrelAudioComponent();

	void FindReloadAudioComponent();

	void FindTurretAudioComponent();

	void InputBinding();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void FiringStateUI();

	void MoveBarrelTowards(FVector AimInDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 1;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 20;

	double LastFireTime = 0;
	
	FVector AimDirection;

	//Degree to front, from + to - range
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float FrontFiringDegreeRange = 13.f;

	//Min Barrel Elevation
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float BarrelMinElevation = 0.f;

	//Applies to FrontFiringDegreeRange only
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float BarrelMinElevationFront = -8.f;

	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	UPROPERTY()
	UAudioComponent* ReloadAudioComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float MinMaxElevateSound = 0.6f;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float MinMaxTurretSound = 0.2f;

	UPROPERTY()
	UAudioComponent* AudioBarrelComponent = nullptr;

	UPROPERTY()
	UAudioComponent* AudioTurretComponent = nullptr;
	
};
