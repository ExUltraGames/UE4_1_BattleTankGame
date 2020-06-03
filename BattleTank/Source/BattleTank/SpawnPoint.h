// Copyright theZombieroom

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnPoint.generated.h"


// Forward Declaration
class ASprungWheel;// remember #include "SprungWheel.h" in .cpp

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawnPoint();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const; // Getter > return pointer to actor spawned
	//AActor* GetSpawnedActor() const {return SpawnedActor;} // could do this rather than in cpp as so simple

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASprungWheel> SpawnClass; // change to type of AActor to redue BP Spawn Class list

	UPROPERTY() // Garbage collection so use a Uproperty
	AActor* SpawnedActor; // For Getter

};
