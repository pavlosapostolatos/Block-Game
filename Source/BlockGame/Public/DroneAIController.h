// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Drone.h"
#include "DroneAIController.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API ADroneAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* BTAsset;

protected:
	
	UPROPERTY(BlueprintReadWrite)
	ADrone* DronePawn;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
};
