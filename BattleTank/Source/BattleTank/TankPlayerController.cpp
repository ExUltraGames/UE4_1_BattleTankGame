// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()// so we can log out
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play Intercepted"));

    //log if possesing Tank // check if GetControlledTank is working // similar to BP
    //auto ControlledTank = GetControlledTank() and replace ControlledTank inot below // auto = keyword declares a variable in the automatic storage class
    if(!GetControlledTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *GetControlledTank()->GetName());
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn()); //returns pawn player controller possessing // cast forces a data type to be converted  
}