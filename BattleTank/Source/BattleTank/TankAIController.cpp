// copyright theZombieroom
#include "Tank.h"
#include "TankAIController.h"
#include "BattleTank.h"
//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()// so we can log out
{
    Super::BeginPlay();
}

//tick // runs every frame setup use super
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); // get player pawn and cast to a tank
    auto ControlledTank = Cast<ATank>(GetPawn());

    if (ensure(PlayerTank && ControlledTank)) // protects pointers
    {
        MoveToActor(PlayerTank, AcceptanceRadius);

        ControlledTank->AimAt(PlayerTank->GetActorLocation());
    }
}