// Copyright theZombieroom


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	//TODO remove magic numbers - remove and go to BP
	TankSpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("TankSpringConstraint"));
	SetRootComponent(TankSpringConstraint);
	TankSpringConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 2);
	TankSpringConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 2);
	TankSpringConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0);
	TankSpringConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 2);
	TankSpringConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 2);
	TankSpringConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 2);
	TankSpringConstraint->SetLinearPositionDrive
	(
		false,
		false,
		true
	);
	TankSpringConstraint->SetLinearVelocityDrive
	(
		false,
		false,
		true
	);
	FVector TankPositionTarget = FVector(0, 0, 120);
	TankSpringConstraint->SetLinearPositionTarget(TankPositionTarget);
	FVector TankVelocityTarget = FVector(0, 0, 0);
	TankSpringConstraint->SetLinearVelocityTarget(TankVelocityTarget);
	TankSpringConstraint->SetLinearDriveParams(500, 100, 0);


	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(TankSpringConstraint);
	Axle->SetSimulatePhysics(true);
	Axle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Wheel->SetNotifyRigidBodyCollision(true); // needed for OnHit 

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
	AxleWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 2);
	AxleWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 2);
	AxleWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 2);
	AxleWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 2);
	AxleWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 2);
	AxleWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 2);
	AxleWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0);
	AxleWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 2);
	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraints();
}


//instead of early returns in BeginPlay = cleaner, create a new function
void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	TankSpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}


// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)//double check // change when physics appplied in frame
	{
		TotalForceMagnitudeThisFrame = 0.f; // reset after force applied
		//UE_LOG(LogTemp, Warning, TEXT("Tick %f"), GetWorld()->GetTimeSeconds());// want whn happening in frame
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude) // apply to each wheel
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
	//UE_LOG(LogTemp, Warning, TEXT("OnHit %f"), GetWorld()->GetTimeSeconds());// want whn happening in frame
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}
