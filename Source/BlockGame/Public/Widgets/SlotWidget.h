#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

UCLASS()
class BLOCKGAME_API USlotWidget : public UUserWidget
{
public:


private:
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	int amount;

public:
};