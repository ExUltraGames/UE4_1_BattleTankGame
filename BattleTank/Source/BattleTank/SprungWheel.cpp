// Copyright theZombieroom


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);//IWYU
	
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	//Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); // use below instead
	Wheel->SetupAttachment(Mass);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	//PhysicsConstraint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	PhysicsConstraint->SetupAttachment(Mass);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

