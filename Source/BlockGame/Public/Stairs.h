// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockBox.h"
#include "GameFramework/Actor.h"
#include "Stairs.generated.h"

UCLASS()
class BLOCKGAME_API AStairs : public ABlockBox
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStairs();
	
	virtual UE::Math::TQuat<double> GetRotation(FVector originLocation, FVector SpawnLocation) override;

protected:


public:
};
