#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API UBTT_ChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY()
	ACharacter* Drone;

	UBehaviorTreeComponent* OwnerCompField = nullptr;//hacky way of UBTTask_BlueprintBase

	UPROPERTY()
	FVector PrevPosition = FVector::Zero();
	
	UPROPERTY(EditAnywhere)
	int Speed = 200;

	UPROPERTY()
	FTimerHandle TimerHandle;

	FTimerDelegate::TMethodPtr<UBTT_ChasePlayer> CheckStuckEvent = &UBTT_ChasePlayer::CheckStuck;

	UFUNCTION()
	void CheckStuck();
protected:
	UBTT_ChasePlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	                            EBTNodeResult::Type TaskResult) override;
};
