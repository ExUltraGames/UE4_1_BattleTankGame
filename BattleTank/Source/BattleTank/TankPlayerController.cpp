// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

//setup beginplay // use super
void ATankPlayerController::BeginPlay()// so we can log out
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play Intercepted"));

    //log if possesing Tank // check if GetControlledTank is working // similar to BP
    //auto ControlledTank = GetControlledTank() and replace ControlledTank in below // auto = keyword declares a variable in the automatic storage class
    if(!GetControlledTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *GetControlledTank()->GetName());
    }
}

//tick // runs every frame setup use super
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrossHair();
    //UE_LOG(LogTemp, Warning, TEXT("PlayerController TICK Intercepted"));
     
}

//method returns a pointer of tank possesed
ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn()); //returns pawn player controller possessing // cast forces a data type to be converted  
}


//testing Aiming component, set to 1.0 and true (we hit something and at location 1,1,1)
void ATankPlayerController::AimTowardsCrossHair()
{
    if(!GetControlledTank())    { return; }
    // using out parameter for this // don't in unreal use define OUT
    FVector HitLocation; // out parameter// don't initialise
    if(GetSightRayHitLocation(HitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString()); // outing variable to console
    }
    
    //tellcontroller tank to aim at his point
}
//GetWorld Location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    //OutHitLocation = FVector(1.0);//test demoing 1,1,1 vector that this function works
    
    //find crosshair posititon in pixel co-ords
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    //UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s"), *ScreenLocation.ToString());

    //De-project screen position to a a world direction
    //line trace along look direction, see hwat hit up to max range
    return true;
}