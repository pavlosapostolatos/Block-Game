#pragma once
#include "BlockBoxInteractive.h"
#include "BlockBoxGreen.generated.h"

UCLASS()
class BLOCKGAME_API ABlockBoxGreen : public ABlockBoxInteractive //maybe abstract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockBoxGreen();

protected:


public:
	virtual void Interact() override;
};
