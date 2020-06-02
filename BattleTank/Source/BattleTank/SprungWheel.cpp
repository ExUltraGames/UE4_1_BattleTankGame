// Copyright theZombieroom


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	////Axle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Axle->SetupAttachment(SpringConstraint);
	//Axle->SetMassOverrideInKg(NAME_None, 1000.0f);
	//////Axle->SetNotifyRigidBodyCollision(false); // required for OnHit events
	//Axle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
	//Axle->SetCollisionObjectType(ECC_WorldStatic);
	//Axle->SetSimulatePhysics(true);
	//auto Location = Axle->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Location of Axle: %s "), *Location.ToString());
	//Location.Z = -120;
	//Axle->SetRelativeLocation(Location);
	//UE_LOG(LogTemp, Warning, TEXT("Location of Axle: %s "), *Location.ToString());

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	//AxleWheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepWorldTransform);
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	////Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetupAttachment(Axle); // want wheel and axle at same place
	//Wheel->SetMassOverrideInKg(NAME_None, 1000.0f);
	//Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Wheel->SetCollisionObjectType(ECC_WorldDynamic);
	//Wheel->SetSimulatePhysics(true);
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
	UE_LOG(LogTemp, Warning, TEXT("Bodyroot is: %s"), *BodyRoot->GetName());
	SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);// remember to change this
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

