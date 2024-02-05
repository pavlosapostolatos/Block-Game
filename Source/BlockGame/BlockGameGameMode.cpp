// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlockGameGameMode.h"
#include "BlockGameCharacter.h"
#include "DroneSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

ABlockGameGameMode::ABlockGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ABlockGameGameMode::StartPlay()
{
	Super::StartPlay();

	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(this, ADroneSpawner::StaticClass(), temp);
	for (auto Temp : temp)
	{
		DroneSpawners.Add(Cast<ADroneSpawner>(Temp));
	}

	StartWave();
}

void ABlockGameGameMode::StartWave()
{
	Wave++;

	UKismetSystemLibrary::PrintString(this, " Starting Wave: " + FString::FromInt(Wave));

	EnemiesPerWave += 4 + sqrt(Wave);

	for (int i = 0; i < EnemiesPerWave; ++i)
	{
		ADrone* Drone = DroneSpawners[rand() % DroneSpawners.Num()]->SpawnDrone();
		Drone->GetDeathDelegate().AddDynamic(this, &ABlockGameGameMode::DroneDeathListener);
	}

	EnemiesAlive = EnemiesPerWave;
	Cast<ABlockGameCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))->GetMainHud()->SetWave(Wave);
}

void ABlockGameGameMode::DroneDeathListener()
{
	if (--EnemiesAlive <= 0)
	{
		StartWave();
	}
}
