#pragma once

#include "CoreMinimal.h"
#include "BlockBoxInteractive.h"
#include "GameFramework/Actor.h"
#include "ChestBox.generated.h"

UCLASS()
class BLOCKGAME_API AChestBox : public ABlockBoxInteractive//maybe abstract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChestBox();

protected:


public:
	virtual void Interact() override;
};
