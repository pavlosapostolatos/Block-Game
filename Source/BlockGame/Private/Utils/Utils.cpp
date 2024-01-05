#include "Utils.h"
#include "BlockBox.h"
#include "Kismet/KismetSystemLibrary.h"

bool checkBoxOverlap( const UObject* WorldContextObject, FTransform SpawnTransform)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> temp;
	TArray<AActor*> temp2;
	TArray<AActor*> temp3;

	if(UKismetSystemLibrary::BoxOverlapActors(WorldContextObject, SpawnTransform.GetLocation(), FVector(49, 49, 49), temp,
											  ABlockBox::StaticClass(), temp2, temp3))
		return true;
	return false;
}
