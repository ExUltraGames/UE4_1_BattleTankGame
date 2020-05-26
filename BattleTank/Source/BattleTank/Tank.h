// Copyright EmbraceIT Ltd.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Tank.generated.h" // Put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//called by engine when actor damage is dealt
	virtual float TakeDamage (float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//returns current health as a percentage of startinghealth 0to1
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	FTankDelegate OnDeath;// no () on this

private:
	
	ATank();
	// Sets default values for this pawn's properties
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)// only change in code but need visible
	int32 CurrentHealth = StartingHealth; // make int as don't want to compare floats

	//virtual void BeginPlay() override;

	//void ApplyDownForce();

	//UFUNCTION()
	//void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void GetReversedHit(const FHitResult& Hit);
}; 
