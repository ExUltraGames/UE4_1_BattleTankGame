// Copyright theZombieroom

#pragma once

//#include "TankAimingComponent.h" // for #include for aiming pointer in protected / / forward declaration - UTankAimingComponent // move to #include to cpp
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
private:
	
	ATank();
	
	virtual void BeginPlay();

};
