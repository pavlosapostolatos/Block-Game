// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTT_MoveDrone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("MoveToLocationInAir");

	ACharacter* Drone = Cast<ACharacter>(Cast<AController>(OwnerComp.GetOwner())->GetPawn());
	
	FVector DroneLocation = Drone->GetActorLocation();

	if (UKismetMathLibrary::EqualEqual_VectorVector(DroneLocation, TargetLocation, 10))
	{
		Drone->GetCharacterMovement()->Velocity = FVector::Zero();
	}
	else
	{
		FVector Velocity = TargetLocation - DroneLocation;
		Velocity.Normalize();
		Velocity *= 200;
		Drone->GetCharacterMovement()->Velocity = Velocity;
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}