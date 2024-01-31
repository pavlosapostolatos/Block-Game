#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boxes/BlockBox.h"
#include "Weapons/Gun.h" 
#include "Inventory.generated.h"

UENUM()
enum class InventoryType : uint8
{
	BLOCK,
	WEAPON
};

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
	InventoryType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UTP_WeaponComponent> C_WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGun> C_WeaponActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Amount;
public:
	FInventory(UTexture2D* Icon, const TSubclassOf<ABlockBox>& C_Box, InventoryType Type,
			const TSubclassOf<UTP_WeaponComponent>& C_WeaponComponent, uint8 Amount)
			: Icon(Icon),
			  C_Box(C_Box),
			  Type(Type),
			  C_WeaponComponent(C_WeaponComponent),
			  Amount(Amount)
	{
	}
};
