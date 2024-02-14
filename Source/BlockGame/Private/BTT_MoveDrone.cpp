// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UBTT_MoveDrone::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("MoveToLocationInAir");

	ACharacter* Drone = Cast<ACharacter>(OwnerComp.GetOwner()); //TODO maybe this is the controller
	FVector DroneLocation = Drone->GetActorLocation();

	if (UKismetMathLibrary::EqualEqual_VectorVector(DroneLocation, TargetLocation, 10))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FVector Velocity = DroneLocation - TargetLocation;
		Velocity.Normalize();
		Velocity *= 200;
		Drone->GetCharacterMovement()->Velocity = Velocity;
	}
}
