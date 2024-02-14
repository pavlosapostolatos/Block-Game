#include "BTT_GetRandomPointInAir.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


EBTNodeResult::Type UBTT_GetRandomPointInAir::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Drone = Cast<AController>(OwnerComp.GetOwner())->GetPawn();
	FVector PotentialLocation;
	do
	{
		auto UnitVector = UKismetMathLibrary::RandomUnitVector();
		float Scale = UKismetMathLibrary::RandomFloatInRange(300, 500);
		PotentialLocation = Scale * UnitVector + Drone->GetActorLocation();
		DrawDebugSphere(GetWorld(), PotentialLocation, 10, 12, FLinearColor::Red.ToFColor(false), false, 10);
	}
	while (TraceDroneMovementCollision(Drone, PotentialLocation));
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("MoveToLocationInAir" ,PotentialLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return Super::ExecuteTask(OwnerComp, NodeMemory);//SUCCESS
}

bool UBTT_GetRandomPointInAir::TraceDroneMovementCollision(AActor* Drone, const FVector& PotentialLocation) const
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic)); // Add WorldStatic objects
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic)); // Add WorldDynamic objects

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Drone);
	IgnoredActors.Add(UGameplayStatics::GetPlayerCharacter(this, 0));

	TArray<FHitResult> OutHits;
	return UKismetSystemLibrary::SphereTraceMultiForObjects(this, Drone->GetActorLocation(), PotentialLocation, 25,
	                                                        ObjectTypes, false, IgnoredActors,
	                                                        EDrawDebugTrace::Type::Persistent, OutHits, false);
}
