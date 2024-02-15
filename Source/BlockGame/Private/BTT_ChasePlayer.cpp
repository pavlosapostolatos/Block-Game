#include "BTT_ChasePlayer.h"

#include "Kismet/KismetMathLibrary.h"
#include "BTT_MoveDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UBTT_ChasePlayer::UBTT_ChasePlayer()
{
	bNotifyTick = 1;
	bNotifyTaskFinished = 1;
	Drone = nullptr;
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Drone = Cast<ACharacter>(Cast<AController>(OwnerComp.GetOwner())->GetPawn());
	OwnerCompField = &OwnerComp;//super dodgy. cannot do it like UBTTask_BlueprintBase::FinishExecute

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, CheckStuckEvent, 5, true);

	return EBTNodeResult::Type::InProgress;// will keep it ticking
}

void UBTT_ChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const FVector TargetLocation = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
	
	const FVector DronePosition = Drone->GetActorLocation();
	const FRotator StartRotation = Drone->GetActorRotation();
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(DronePosition, TargetLocation);
	Drone->SetActorRotation(FMath::Lerp(StartRotation, TargetRotation, 0.025));

	
	if (UKismetMathLibrary::EqualEqual_VectorVector(DronePosition, TargetLocation, 100))
	{
		Drone->GetCharacterMovement()->Velocity = FVector::Zero();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FVector Velocity = TargetLocation - DronePosition;
		Velocity.Normalize();
		Velocity *= Speed;
		Drone->GetCharacterMovement()->Velocity = Velocity;
		// Drone->GetCharacterMovement()->GroundFriction = 0.0f;
		// Drone->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		// Drone->GetCharacterMovement()->bUseSeparateBrakingFriction = false;
	}
}

void UBTT_ChasePlayer::CheckStuck()
{

	const FVector CurrentPosition = Drone->GetActorLocation();
	if(UKismetMathLibrary::EqualEqual_VectorVector(CurrentPosition, PrevPosition, 100))
	{
		FinishLatentTask(*OwnerCompField, EBTNodeResult::Failed);
	}
	PrevPosition = CurrentPosition;
}

void UBTT_ChasePlayer::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
