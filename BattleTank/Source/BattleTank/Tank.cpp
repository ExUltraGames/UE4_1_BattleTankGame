// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//SetActorEnableCollision(true);

	Tank = CreateDefaultSubobject<UStaticMeshComponent>(FName("Tank"));
	SetRootComponent(Tank);
	//set physics and collision defaults
	Tank->SetNotifyRigidBodyCollision(true);
	Tank->SetSimulatePhysics(true);
	Tank->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Tank->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Tank->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	//TurretPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("TurretPhysicsConstraint"));
	//TurretPhysicsConstraint->SetupAttachment(Tank, FName("Turret"));

	TankTurret = CreateDefaultSubobject<UTankTurret>(FName("TankTurret"));
	TankTurret->SetupAttachment(Tank, FName("Turret"));
	TankTurret->SetSimulatePhysics(false);
	//auto TurretSocket = TankTurret->GetAttachSocketName();
	//UE_LOG(LogTemp, Warning, TEXT("TurretSocket: %s"), *TurretSocket.ToString());

	//BarrelPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BarrelPhysicsConstraint"));
	//BarrelPhysicsConstraint->SetupAttachment(Tank, FName("Turret"));

	TankBarrel = CreateDefaultSubobject<UTankBarrel>(FName("TankBarrel"));
	TankBarrel->SetupAttachment(TankTurret, FName("Barrel"));
	TankBarrel->SetSimulatePhysics(false);


	TankMovement = CreateDefaultSubobject<UTankMovementComponent>(FName("TankMovement"));
	TankMovementAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("TankMovementAudioComponent"));
	TankMovementAudioComponent->bAutoActivate = true;
	
	TankAiming = CreateDefaultSubobject<UTankAimingComponent>(FName("TankAiming"));
	TankReloadAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("TankReloadAudioComponent"));
	TankReloadAudioComponent->bAutoActivate = true;
	TankAimingAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("TankAimingAudioComponent"));
	TankAimingAudioComponent->bAutoActivate = false;
	TankTurretAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("TankTurretAudioComponent"));
	TankTurretAudioComponent->bAutoActivate = false;
	
	//could add exhaust component too
	//Exhaust = CreateDefaultSubobject<UParticleSystemComponent>(FName("Exhaust"));
	//Exhaust->SetupAttachment(RootComponent, TEXT("Exhaust"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
	InputBinding();
	//SetupConstraints();
}


void ATank::InputBinding()
{
	InputComponentCameraBinding = FindComponentByClass<UInputComponent>();
	
	if (InputComponentCameraBinding)
	{
		InputComponentCameraBinding->BindAxis("AimAzimuth", this, &ATank::RotateCameraYaw);//out float AxisValue =  speed & direction
		InputComponentCameraBinding->BindAxis("AimAltitude", this, &ATank::RotateCameraPitch);
		//UE_LOG(LogTemp, Warning, TEXT("AimAzimuth Component found")); // to test
	}
}

void ATank::SetupConstraints()
{
	//TurretPhysicsConstraint->SetConstrainedComponents(Tank, NAME_None, TankTurret, NAME_None);
	BarrelPhysicsConstraint->SetConstrainedComponents(TankTurret, NAME_None, TankBarrel, NAME_None);
}

void ATank::RotateCameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue; // value = speed and direction
	AzimuthGimbal = FindComponentByClass<USceneComponent>()->GetChildComponent(1.f);
	AzimuthGimbalBarrel = GetDefaultSubobjectByName(TEXT("Azimuth Gimbal Barrel"));

	if (AzimuthGimbal)
	{
		FRotator NewRotation = AzimuthGimbal->GetComponentRotation();
		//UE_LOG(LogTemp, Warning, TEXT("AimGimbal is: %s"), *AzimuthGimbal->GetName());
		NewRotation.Yaw += CameraInput.X;
		AzimuthGimbal->SetWorldRotation(NewRotation);
	}
	if (AzimuthGimbalBarrel)
	{ 
		FRotator NewRotation = Cast<USceneComponent>(AzimuthGimbalBarrel)->GetComponentRotation();
		CameraInputClamped.X = FMath::Clamp(CameraInput.X, CameraBarrelClampMin, CameraBarrelClampMax); // slows mouse / barrel reaction in barrel view
		NewRotation.Yaw = NewRotation.Yaw + CameraInputClamped.X;
		Cast<USceneComponent>(AzimuthGimbalBarrel)->SetWorldRotation(NewRotation);
	}
}

void ATank::RotateCameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
	SpringArmPitch = GetDefaultSubobjectByName(TEXT("SpringArm"));
	SpringArmPitchBarrel = GetDefaultSubobjectByName(TEXT("SpringArm Barrel"));

	if (SpringArmPitch)
	{
		FRotator NewRotation = Cast<USceneComponent>(SpringArmPitch)->GetComponentRotation();
		//UE_LOG(LogTemp, Warning, TEXT("SpringArm is: %s"), *SpringArmPitch->GetName());
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, CameraPitchMin, CameraPitchMax);
		Cast<USceneComponent>(SpringArmPitch)->SetWorldRotation(NewRotation);
	}
	if (SpringArmPitchBarrel)
	{
		FRotator NewRotation = Cast<USceneComponent>(SpringArmPitchBarrel)->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, CameraPitchBarrelMin, CameraPitchBarrelMax);
		Cast<USceneComponent>(SpringArmPitchBarrel)->SetWorldRotation(NewRotation);
	}
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth; // cast healths to floats
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount); // turn float to int
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth); // needs <int32>

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast(); // listeners now decide what to do
	}

	//UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f, DamageToApply: %i"), DamageAmount, DamageToApply);// note %f and %i

	return DamageToApply;
}	

//leave in as this is how apply to actor
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();
//	OnActorHit.AddDynamic(this, &ATank::OnHit);
//	//OnComponentHit.AddDynamic(this, &ATank::OnHit); // TODO simulate Generates hit events enable // SetActorEnableCollision(true);
//}
//
//void ATank::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
//{	
//	ApplyDownForce();
//}
//
//
//void ATank::ApplyDownForce()
//{	
//	
//	auto FlySpeed = FVector::DotProduct(GetActorUpVector(), GetVelocity());
//	UE_LOG(LogTemp, Warning, TEXT("FlySpeed: %f"), FlySpeed);
//	// Work-out the required acceleration this frame to correct
//	auto DeltaTime = GetWorld()->GetDeltaSeconds(); // get it when need it and don't need to pass in
//	auto CorrectionAcceleration = -FlySpeed / DeltaTime * GetActorUpVector();
//
//	// Calculate and apply sideways (F = m a)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // TODO change to TANK not Root ? GetOwner?
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration); 
//	TankRoot->AddForce(CorrectionForce);
//}