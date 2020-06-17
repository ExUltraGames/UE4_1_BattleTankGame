// Copyright EmbraceIT Ltd.

#pragma once

#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/Object.h"
#include "Particles/ParticleSystemComponent.h"
#include "Tank.generated.h" // Put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
// Forward Declaration
class UTankBarrel;
class UTankTurret;
class UTankMovementComponent;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//called by engine when actor damage is dealt
	virtual float TakeDamage (float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//returns current health as a percentage of startinghealth 0to1
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	FTankDelegate OnDeath;// no () on this

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UTankTurret* TankTurret = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UTankBarrel* TankBarrel = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UTankMovementComponent* TankMovement = nullptr;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UTankAimingComponent* TankAiming = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* TurretAudioComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* BarrelAudioComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* TankMovementAudioComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* TankAimingAudioComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* TankReloadAudioComponent = nullptr;
protected:


private:
	
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)// only change in code but need visible
	int32 CurrentHealth; // remove initiliase otherwise always = 100 // intiliase in BeginPlay not constructor

	//virtual void BeginPlay() override;

	//void ApplyDownForce();

	//UFUNCTION()
	//void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void GetReversedHit(const FHitResult& Hit);

	void InputBinding();

	UPROPERTY()
	UInputComponent* InputComponentCameraBinding = nullptr;

	UPROPERTY()
	USceneComponent* AzimuthGimbal = nullptr;

	UPROPERTY()
	UObject* AzimuthGimbalBarrel = nullptr;

	UPROPERTY()
	UObject* SpringArmPitch = nullptr;

	UPROPERTY()
	UObject* SpringArmPitchBarrel = nullptr;

	//UPROPERTY()
	//UObject* SpringArmPitch = nullptr;

	//UPROPERTY()
	//UObject* SpringArmPitchBarrel = nullptr;

	void RotateCameraYaw(float AxisValue);
	void RotateCameraPitch(float AxisValue);

	FVector2D CameraInput;
	FVector2D CameraInputClamped;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CameraPitchMax = -5.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CameraPitchMin = -60.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CameraPitchBarrelMax = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CameraPitchBarrelMin = -20.0f;
	//adjusts speed relationship of barrel to mouse
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CameraBarrelClampMax = 1.f;
	//adjusts speed relationship of barrel to mouse
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CameraBarrelClampMin = -1.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* Exhaust = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Tank = nullptr;

}; 
