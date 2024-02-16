#include "BTT_CheckIsCharacterStuck.h"
#include "BTT_ChasePlayer.h"

#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

UBTT_CheckIsCharacterStuck::UBTT_CheckIsCharacterStuck()
{
	bNotifyTick = 1;
	bTickIntervals = true;
	// bNotifyTaskFinished = 1;
}

EBTNodeResult::Type UBTT_CheckIsCharacterStuck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	SetNextTickTime(NodeMemory, 5);

	return EBTNodeResult::Type::InProgress;// will keep it ticking
}

void UBTT_CheckIsCharacterStuck::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UKismetSystemLibrary::PrintString(this, "DeltaSeconds: " + FString::SanitizeFloat(DeltaSeconds));
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	SetNextTickTime(NodeMemory, 5);

	const FVector PreviousLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PreviousLocation");
	const ACharacter* Drone = Cast<ACharacter>(Cast<AController>(OwnerComp.GetOwner())->GetPawn());
	const FVector DronePosition = Drone->GetActorLocation();

	if(UKismetMathLibrary::EqualEqual_VectorVector(DronePosition, PreviousLocation, 100))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("PreviousLocation", DronePosition);
	}
}
