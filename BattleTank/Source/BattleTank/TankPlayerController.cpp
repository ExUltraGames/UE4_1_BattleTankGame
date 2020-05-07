// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

//setup beginplay // use super
void ATankPlayerController::BeginPlay()// so we can log out
{
    Super::BeginPlay();
    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) {return;}
    FoundAimingComponent(AimingComponent);// to pass for BlueprintImplementableEvent
}

//tick // runs every frame setup use super
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrossHair();
}

//method returns a pointer of tank possesed
ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn()); //returns pawn player controller possessing // cast forces a data type to be converted  
}

void ATankPlayerController::AimTowardsCrossHair()
{
    if(!ensure(GetControlledTank()))    { return; }
    FVector HitLocation; // out parameter// don't initialise
    if(GetSightRayHitLocation(HitLocation))
    {
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
   
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        //line trace along look direction, see hwat hit up to max range
        GetLookVectorHitLocation(LookDirection, HitLocation); // functions sets the hitlocation to OUT from GetSightRayHitLocation
    }
    
    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const //bool as need a success result
{
    FHitResult HitResult;  // stre the hit result as an FHitResult
    auto StartLocation = PlayerCameraManager->GetCameraLocation(); // playercameramanager is a variable of APlayerController
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

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


