// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // projectile doesn't need to tick // tick removed

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LaunchBlastForce = CreateDefaultSubobject<URadialForceComponent>(FName("Launch Blast Force"));
	LaunchBlastForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);// newer API
	ImpactBlast->bAutoActivate = false; // don't want activated at start

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force")); 
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Impact SFX"));
	AudioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); // as actor not component register / get in scope to collisionmesh
}

void AProjectile::LaunchProjectile(float Speed)
{

	//TODO put a delay before fire and a "fire shout" sound effect
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
	LaunchBlastForce->FireImpulse();
	LaunchBlastActivate();
	if (bLaunch && !bWhistle)
	{
		FTimerHandle Delay;
		GetWorld()->GetTimerManager().SetTimer(Delay, this, &AProjectile::WhistleActivate, WhistleDelay, false);
		bLaunch = false;
	}

	//TODO add LaunchBlast Impulse
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{	
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	ImpactBlastActivate();
	bWhistle = true;
	
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(), //already in projectile
		ExplosionForce->Radius, // for consistency // like via Explosionforce to its radius
		UDamageType::StaticClass(),
		TArray<AActor*>() // an empty array of actor pointers
	);


	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

}
void AProjectile::OnTimerExpire()
{
	Destroy();
}

void AProjectile::ImpactBlastActivate()
{
	if (ImpactBlastSFX)
	{
	AudioComponent->SetSound(ImpactBlastSFX);
	AudioComponent->Play();
	}

	if (ImpactShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(FireShake, 1);
	}
}

void AProjectile::LaunchBlastActivate()
{
	if (LaunchBlastSFX)
	{
	AudioComponent->SetSound(LaunchBlastSFX);
	AudioComponent->Play();
	bLaunch = true;
	}
	if (FireShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(FireShake, 1);
	}
}

void AProjectile::WhistleActivate()
{
	if(!bWhistle) 
	{
		AudioComponent->SetSound(WhistleSFX);
		AudioComponent->Play();
	}
	bWhistle = false;
}