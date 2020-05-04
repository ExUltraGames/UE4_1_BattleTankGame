// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()// so we can log out
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play Intercepted"));
    // reuse testing code // would remove from final product
    // if(!GetControlledTank())
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a Tank"));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *GetControlledTank()->GetName());
    // }

//      if(!GetPlayerTank()) // don'e need to check anymore
//     {
//         UE_LOG(LogTemp, Warning, TEXT("AIController can't find player Tank"));
//     }
//     else
//     {
//         UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *GetPlayerTank()->GetName());
//     }
}

//tick // runs every frame setup use super
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("PlayerController TICK Intercepted"));
    // Defactoring GetControlledTank and GetPlayerTank into below:
    // if(GetPlayerTank()) // no point running if no player tank
    // {
    //MOve towards the player
    //     //Aim towards player
    //     GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    //     GetControlledTank()->Fire(); // fire method from Tank.h // fire every frame
    // }

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); // get player pawn and cast to a tank
    auto ControlledTank = Cast<ATank>(GetPawn());
    // if (ControlledTank)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("AIController possessing Tank: %s"), *ControlledTank->GetName());
    // }
    if (PlayerTank && ControlledTank) // protects pointer
    {
        MoveToActor(PlayerTank, AcceptanceRadius);

        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        //UE_LOG(LogTemp, Warning, TEXT("AITank %s Aiming at: %s"), *ControlledTank->GetName(), *PlayerTank->GetName() );
        //ControlledTank->Fire(); // TODO limit firing rate
    }
}

// ATank* ATankAIController::GetControlledTank() const /// returns possed tank
// {
//     return Cast<ATank>(GetPawn()); //returns pawn player controller possessing // cast forces a data type to be converted  
// }

// ATank* ATankAIController::GetPlayerTank() const // returns the player thank for the AI to target
// {
//     //if(!GetWorld()->GetFirstPlayerController()->GetPawn())
//     // {
//     //     return nullptr; // return early // not needed as GetWorld would fail, don't need to protect in GETWORLD
//     // }
//          return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
//         // UE_LOG(LogTemp, Warning, TEXT("PLayerTank is: %s"), GetWorld()->GetFirstPlayerController()->GetPawn()); - needs to be in begin play, use previous written code as we have tested already
// }