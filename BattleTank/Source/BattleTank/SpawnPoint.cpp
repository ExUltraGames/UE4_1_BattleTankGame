// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "SpawnPoint.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());//IWYU // this spawns at correct location
	//UE_LOG(LogTemp,Warning, TEXT("After Spawn"));
	if (!NewActor) {return;}
	//NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	//above not working in BeginPlay// use Logs to see what wrong // error due to order created // do differently // use SpawnActorDeffered() and FinishSpawningActor()
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);//change to World, as location of spawn already set
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

