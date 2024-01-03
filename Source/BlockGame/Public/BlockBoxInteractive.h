#pragma once

#include "CoreMinimal.h"
#include "BlockBox.h"
#include "GameFramework/Actor.h"
#include "BlockBoxInteractive.generated.h"

UCLASS()
class BLOCKGAME_API ABlockBoxInteractive : public ABlockBox//maybe abstract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockBoxInteractive();

protected:


public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact();
};


