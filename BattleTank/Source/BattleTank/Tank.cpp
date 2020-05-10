// Copyright theZombieroom


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // removed tick as not needed = optimisation
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}





