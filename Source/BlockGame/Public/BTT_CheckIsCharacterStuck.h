#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_CheckIsCharacterStuck.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API UBTT_CheckIsCharacterStuck : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int Speed = 200;

protected:
	UBTT_CheckIsCharacterStuck();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	//                             EBTNodeResult::Type TaskResult) override;
};
