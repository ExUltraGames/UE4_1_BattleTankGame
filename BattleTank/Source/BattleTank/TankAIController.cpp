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

     if(!GetPlayerTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController can't find player Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *GetPlayerTank()->GetName());
    }
}

//tick // runs every frame setup use super
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("PlayerController TICK Intercepted"));
    if(GetPlayerTank()) // no point running if no player tank
    {
        //MOve towards the player

        //Aim towards player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        
        //Fire if ready
    }
}

ATank* ATankAIController::GetControlledTank() const /// returns possed tank
{
    return Cast<ATank>(GetPawn()); //returns pawn player controller possessing // cast forces a data type to be converted  
}

ATank* ATankAIController::GetPlayerTank() const // returns the player thank for the AI to target
{
    //if(!GetWorld()->GetFirstPlayerController()->GetPawn())
    // {
    //     return nullptr; // return early // not needed as GetWorld would fail, don't need to protect in GETWORLD
    // }
         return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
        // UE_LOG(LogTemp, Warning, TEXT("PLayerTank is: %s"), GetWorld()->GetFirstPlayerController()->GetPawn()); - needs to be in begin play, use previous written code as we have tested already
}