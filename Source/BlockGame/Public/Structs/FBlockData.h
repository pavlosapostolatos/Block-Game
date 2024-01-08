#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBox.h"
#include "FBlockData.generated.h"

USTRUCT(BlueprintType)
struct FBlockData
{
	GENERATED_BODY()

	FBlockData() = default;
	
	FBlockData(const TSubclassOf<class ABlockBox>& Type, const FVector3d& Location, const FRotator& Rotation)
		: type(Type),
		  location(Location),
		  rotation(Rotation)
	{
	}
	UPROPERTY(BlueprintReadOnly, Category = Tutorial)
	TSubclassOf<ABlockBox> type;
	
	UPROPERTY(BlueprintReadOnly, Category = Tutorial)
	FVector location;
	
	UPROPERTY(BlueprintReadOnly, Category = Tutorial)
	FRotator rotation;

	inline bool operator == (const FBlockData& other) const
	{
		return type == other.type && location.Equals(other.location) && rotation.Equals(other.rotation) ;
	}
};

uint32 GetValueTypeHash(const FBlockData& Src);
uint32 GetTypeHash(const FBlockData& other);

