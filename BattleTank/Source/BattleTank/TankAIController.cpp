// copyright theZombieroom

#include "TankAIController.h"
#include "TankAimingComponent.h"
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
 
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); // get player pawn
    auto ControlledTank = GetPawn();

    if (!ensure(PlayerTank && ControlledTank)) {return;}// protects pointers
        MoveToActor(PlayerTank, AcceptanceRadius);

        auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) {return;}
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
        //UE_LOG(LogTemp, Warning, TEXT("AimingComponent on ControlledTank: %s"), *GetPawn()->GetName());
        AimingComponent->Fire(); // the aimingcomponent that fires
}