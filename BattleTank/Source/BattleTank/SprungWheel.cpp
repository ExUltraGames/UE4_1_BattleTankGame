// Copyright theZombieroom


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

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
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
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

}

