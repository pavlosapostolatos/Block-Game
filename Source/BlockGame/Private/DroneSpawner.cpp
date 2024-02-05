// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneSpawner.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADroneSpawner::ADroneSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ADroneSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADroneSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ADrone* ADroneSpawner::SpawnDrone() const
{
	const FVector Location = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();

	const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Location, Extent);

	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<ADrone>(DroneClass, UE::Math::TTransform(SpawnLocation), Parameters);
}
