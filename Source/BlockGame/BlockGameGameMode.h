// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DroneSpawner.h"
#include "GameFramework/GameModeBase.h"
#include "BlockGameGameMode.generated.h"

UCLASS(minimalapi)
class ABlockGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Body, meta = (AllowPrivateAccess = "true"))
	int EnemiesPerWave = 0;

	int EnemiesAlive = 0;

	UPROPERTY(BlueprintReadWrite, Category = Body, meta = (AllowPrivateAccess = "true"))
	int Wave = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Body, meta = (AllowPrivateAccess = "true"))
	TArray<ADroneSpawner*> DroneSpawners;

protected:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartWave();

public:
	ABlockGameGameMode();

	UFUNCTION()
	void DroneDeathListener();
};
