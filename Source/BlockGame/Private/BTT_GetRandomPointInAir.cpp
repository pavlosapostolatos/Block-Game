#include "BTT_GetRandomPointInAir.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void UBTT_GetRandomPointInAir::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)//TODO maybe use execute
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	ACharacter* Drone = Cast<ACharacter>(OwnerComp.GetOwner());//TODO maybe this is the controller
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
}

bool UBTT_GetRandomPointInAir::TraceDroneMovementCollision(ACharacter* Drone, const FVector& PotentialLocation) const
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
