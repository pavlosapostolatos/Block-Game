#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBox.h"
#include "Kismet/KismetSystemLibrary.h"
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

	bool operator == (const FBlockData& other) const
	{
		// bool a = type == other.type;
		// UKismetSystemLibrary::PrintString(this, FString::FromInt(a));
		//fuck this class equality bullshit

		//WTF is happening here is that we add to the set with TSubclassOf( the statically compiled default UClasses of the BlockBox classes).
		// So when we remove we need to compare with the Uclass of the default BlockBox class
		/** Returns the UClass that defines the fields of this object */
		// FORCEINLINE UClass* GetClass() const
		// {
		// 	return ClassPrivate;
		// }
		// this is what TSubclassOf stores inside it's Class field
		// https://forums.unrealengine.com/t/why-use-tsubclassof-and-not-just-the-class-itself/365690
		// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/TSubclassOf/
		return type.Get() == other.type.Get() && location.Equals(other.location) && rotation.Equals(other.rotation) ;
	}
};

uint32 GetValueTypeHash(const FBlockData& Src);
uint32 GetTypeHash(const FBlockData& other);

