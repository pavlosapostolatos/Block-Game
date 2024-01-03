// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBox.generated.h"

struct DestroyData;

UCLASS()
class BLOCKGAME_API ABlockBox : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category=Mesh)
	UMaterialInterface* BlockMaterial;
	
	
	void DestroyBox(float DeltaTime);

public:
	// Sets default values for this actor's properties
	ABlockBox();

protected:
	struct LerpData
	{
		float LerpAmount = 0.0f;
		float LerpDuration = 3.0f; // Duration in seconds
		float LerpTimer = 0.0f;
		float StartValue = 0.0f;
		float EndValue = 1.0f;
		float bLerping = false;
	};
	
	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* SM_Block;

	LerpData destroyData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateMaterialDestruction(float destroyAmount);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyBox();
};

