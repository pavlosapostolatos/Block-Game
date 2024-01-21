#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Structs/Inventory.h"
#include "SlotWidget.generated.h"

UCLASS()
class BLOCKGAME_API USlotWidget : public UUserWidget
{
public:


private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	UImage* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	int Amount;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActivateSlot();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DeactivateSlot();

	UFUNCTION(BlueprintNativeEvent)
	void GiveAmount(int newAmount);

	void GiveAmount_Implementation(int newAmount)
	{
		Amount = newAmount;
	}

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HideAmount();
	
	UFUNCTION(BlueprintCallable)
	void SetUp(FInventory& Inventory);
};
