#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetRandomPointInAir.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API UBTT_GetRandomPointInAir : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int MinDistance = 300;

	UPROPERTY(EditAnywhere)
	int MaxDistance = 500;
	
	bool TraceDroneMovementCollision(AActor* Drone, const FVector& PotentialLocation) const;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
