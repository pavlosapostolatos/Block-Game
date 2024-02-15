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

	const FVector DronePosition = Drone->GetActorLocation();
	const FRotator StartRotation = Drone->GetActorRotation();
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(DronePosition, TargetLocation);
	Drone->SetActorRotation(FMath::Lerp(StartRotation, TargetRotation, 0.025));
	
	if (UKismetMathLibrary::EqualEqual_VectorVector(DronePosition, TargetLocation, 10))
	{
		Drone->GetCharacterMovement()->Velocity = FVector::Zero();
	}
	else
	{
		FVector Velocity = TargetLocation - DronePosition;
		Velocity.Normalize();
		Velocity *= Speed;
		Drone->GetCharacterMovement()->Velocity = Velocity;
		Drone->GetCharacterMovement()->GroundFriction = 0.0f;
		Drone->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		Drone->GetCharacterMovement()->bUseSeparateBrakingFriction = false;
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}