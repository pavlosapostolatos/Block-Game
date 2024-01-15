#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.h"
#include "ToolbarWidget.generated.h"

UCLASS()
class BLOCKGAME_API UToolbarWidget : public UUserWidget
{
public:


private:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite , meta=(AllowPrivateAccess))
	USlotWidget* ActiveSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	TArray<USlotWidget*> Slots;

public:
	void ActivateSlot(int Index);

	UFUNCTION(BlueprintCallable)
	void SetUp(TArray<FInventory>& Inventory);
};