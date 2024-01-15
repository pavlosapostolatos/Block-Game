#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBox.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FInventory
{
	FInventory() = default;

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABlockBox> C_Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Amount;

public:
	FInventory(UTexture2D* Icon, const TSubclassOf<::ABlockBox>& C_Box, uint8 Amount)
		: Icon(Icon),
		  C_Box(C_Box),
		  Amount(Amount)
	{
	}
};
