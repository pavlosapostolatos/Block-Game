// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs.h"
#include "BlockBox.generated.h"

struct DestroyData;

UCLASS()
class BLOCKGAME_API ABlockBox : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category=Mesh)
	UMaterialInterface* BlockMaterial;
	
	void DestroyBox(float DeltaTime);

protected:
	
	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* SM_Block;

	LerpData destroyData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateMaterialDestruction(float destroyAmount);

public:
	// Sets default values for this actor's properties
	ABlockBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyBox();

	// UFUNCTION(BlueprintCallable)
	virtual UE::Math::TQuat<double> GetRotation(FVector originLocation,FVector SpawnLocation);
};

