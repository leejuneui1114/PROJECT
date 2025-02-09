// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomSpawnManager.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "RotatingPlatform.h"
#include "MovingPlatform.h"


// Sets default values
ARandomSpawnManager::ARandomSpawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumberOfActorsToSpawn = 5;
	SpawnRange = 1000.f;
	SpawnZ = 50.f;

}

TArray<FVector> ARandomSpawnManager:: GenerateGridSpawnLocations() const
{
	TArray<FVector> Locations;

	int32 GridCount = FMath::CeilToInt(FMath::Sqrt((float)NumberOfActorsToSpawn));
	float Step = (GridCount > 1) ? (2 * SpawnRange) / (GridCount - 1) : 0.0f;

	for (int32 Row = 0; Row < GridCount; Row++)
	{
		for (int32 Col = 0; Col < GridCount; Col++)
		{
			if (Locations.Num() >= NumberOfActorsToSpawn)
			{
				break;
			}

			float X = -SpawnRange + Col * Step;
			float Y = -SpawnRange + Row * Step;
			Locations.Add(FVector(X, Y, SpawnZ));



		}


	}
	return Locations;
}


// Called when the game starts or when spawned
void ARandomSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	if (ActorClassesToSpawn.Num() == 0)
	{
		return;
	}

TArray<FVector> GridLocations = GenerateGridSpawnLocations();

for (const FVector& SpawnLocation : GridLocations)
{
	FRotator SpawnRotation(0.f, FMath::RandRange(0.f, 360.f), 0.f);

	const int32 ClassIndex = FMath::RandRange(0, ActorClassesToSpawn.Num() - 1);
	TSubclassOf<AActor> ChosenClass = ActorClassesToSpawn[ClassIndex];

	FActorSpawnParameters SpawnParams;
	AActor* SpawneActor = World->SpawnActor<AActor>(
		ChosenClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (SpawnedActor)
	{
		if (ARotatingPlatform* RotPlatform = Cast < ARotatingPlatform(SpawnedActor))
		{
			RotPlatform->RotationSpeed = FRotator(0.f, FMath::RandRange(30.f, 120.f), 0.f);
			RotPlatform->bUseSinScale = true;
		}
		else if (AMovingPlatform* MovPlatform = Cast<ARotationgPlatform>(SpawnedActor))
		{
			MovPlatform->MoveSpeed = FMath::RandRange(50.f, 300.f);
		}
	}
}

};


