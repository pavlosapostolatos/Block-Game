// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBox.generated.h"


struct DestroyData
{
	float DestroyAmount = 0.0f;
	float LerpDuration = 3.0f; // Duration in seconds
	float LerpTimer = 0.0f;
	float StartValue = 0.0f;
	float EndValue = 1.0f;
	float bLerping = false;
};

UCLASS()
class BLOCKGAME_API ABlockBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	DestroyData destroyData;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyBox();
	void UpdateDestroyAmount(float DeltaTime);
};