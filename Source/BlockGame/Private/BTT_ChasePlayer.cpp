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
	// bNotifyTaskFinished = 1;
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Type::InProgress;// will keep it ticking
}

void UBTT_ChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* Drone = Cast<ACharacter>(Cast<AController>(OwnerComp.GetOwner())->GetPawn());

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
