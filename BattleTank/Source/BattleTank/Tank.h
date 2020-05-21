// Copyright EmbraceIT Ltd.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h" // Put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	//virtual void BeginPlay() override;

	//void ApplyDownForce();

	//UFUNCTION()
	//void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void GetReversedHit(const FHitResult& Hit);
}; 
