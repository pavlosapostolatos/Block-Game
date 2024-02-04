// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drone.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DroneSpawner.generated.h"

UCLASS()
class BLOCKGAME_API ADroneSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Body, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADrone> DroneClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Body, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnBox;
public:	
	// Sets default values for this actor's properties
	ADroneSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Blueprintable)
	void SpawnDrone() const;
};
