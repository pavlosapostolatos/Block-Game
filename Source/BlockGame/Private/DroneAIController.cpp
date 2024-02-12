// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAIController.h"

#include "BlockGame/BlockGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void ADroneAIController::BeginPlay()
{
	Super::BeginPlay();
	DronePawn = Cast<ADrone>(GetInstigator());
}

void ADroneAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector DronePosition = DronePawn->GetActorLocation();
	const FVector PlayerPosition = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
	const FRotator StartRotation = DronePawn->GetActorRotation();
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(DronePosition, PlayerPosition);
	DronePawn->SetActorRotation(FMath::Lerp(StartRotation, TargetRotation, 0.025));
}
