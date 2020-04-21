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
        //UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString()); // outing the final variable to console // all others must work for this to happen
        //tellcontroller tank to aim at his point
        GetControlledTank()->AimAt(HitLocation);
    }
    
   
}
//GetWorld Location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    //OutHitLocation = FVector(1.0);//test demoing 1,1,1 vector that this function works
    
    //find crosshair posititon in pixel co-ords
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation); // could use FVector to be specific rather than auto
    //UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s"), *ScreenLocation.ToString());

    //De-project screen position to a a world direction // refactored into GetLookDirection() below
    // FVector CameraWorldLocation;
    // FVector WorldDirection; // renamed to LookDirection in refactor
    // //bool DeprojectScreenPositionToWorld(float ScreenX,float ScreenY,FVector & WorldLocation,FVector & WorldDirection) const // from docs use below
    // if(DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection)) // if true as a bool
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *WorldDirection.ToString());
    // }

    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        //line trace along look direction, see hwat hit up to max range
        GetLookVectorHitLocation(LookDirection, HitLocation); // functions sets the hitlocation to OUT from GetSightRayHitLocation
        //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());   
    }

    
    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const //bool as need a success result
{
    FHitResult HitResult;  // stre the hit result as an FHitResult
    auto StartLocation = PlayerCameraManager->GetCameraLocation(); // playercameramanager is a variable of APlayerController
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    // if(//Linetrace success) // psuedo code of below
    // {
    //     //set hit location
    //     return true;
    // }
    // return false;

    if(GetWorld()->LineTraceSingleByChannel(
         HitResult, //this is what is OUT
         StartLocation, 
         EndLocation, 
         ECollisionChannel::ECC_Visibility)   // ECollisionChannel TraceChannel = pick the visible channel
          )
    {
        //set hit location
        HitLocation = HitResult.Location; //this gives a vector from hitresult (struct)
        return true;
    }
    HitLocation = FVector(0); // if don't hit anything (i.e.sky) get 0,0,0 and return a false
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const // in parameter = screenlocation, functions OUTs Lookdirection
{
    FVector CameraWorldLocation; // to be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection); // must return as a bool function
}


