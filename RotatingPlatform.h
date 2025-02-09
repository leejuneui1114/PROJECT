// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Compoents")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roation")
	FRotator RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale|SinWave")
	bool bUseSineScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale|SinWave")
	float ScaleFrequency;

	UPROPERTY(EditeAnywhere, BlueprintReadWrite, Category = "Scale|SinWave")
	float ScaleAmplitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scale|SinWave")
	FVector InitialScale;


protected:
	// Called when ths game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ChangeColor();

private :
	FTimerHandle ColorChangeTimerHandle;
	FTimerHandle RepeatingColorChangeTimerHandle;
	

};
