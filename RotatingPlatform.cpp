// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = FRotator(0.f, 45.f, 0.f);
	bUseSineScale = false;
	ScaleFrequency = 1.f;
	ScaleAmplitude = 0.2f;

}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	InitialScale = GetActorScale3D();

	GetWorldTimerManager(). SetTimer(
		ColorChangeTimerHandle,
		this,
		&ARotatingPlatform::ChangeColor,
		5.f,
		false
	);

	GetWorldTimerManager().SetTimer(
		RepeatingColorChangeTimerHandle,
		this,
		&ARotatingPlatform::ChangeColor,
		3.f,
		true



	);
	
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(RotationSpeed * DeltaTime);
	if (bUseSineScale)
	{
		const float Time = GetWorld()->GetTimeSeconds();
		const float SineValue = FMath::Sin(Time * 2.f * PI * ScaleFrequency);
		const float ScaleFactor = 1.f + (ScaleAmplitude * SineValue);
		SetActorScale3D(InitialScale * ScaleFactor);


	}

}

void ARotatingPlatform::ChangeColor()
{
	if (MeshComponent)
	{
		UMaterialInstanceDynamic* DynMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		if (MeshComponent)
		{
			const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
			DynMaterial->SetVectorParameterValue(TEXT("Color"), RandomColor);

		}


	}


}

