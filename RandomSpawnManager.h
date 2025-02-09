// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomSpawnManager.generated.h"

UCLASS()
class SPARTAPROJECT_API ARandomSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomSpawnManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Spawn")
	int32 NumberOfActorsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Spawn")
	TArray<TSubclassOf<AActor>> ActorClassesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Spawn")
	float SpawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Spawn")
	float SpawnZ;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FVector> GenerateGridSpawnLocations() const;

};
