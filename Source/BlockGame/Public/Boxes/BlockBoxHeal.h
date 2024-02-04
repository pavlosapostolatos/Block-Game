#pragma once

#include "CoreMinimal.h"
#include "BlockBoxMagma.h"
#include "BlockBoxHeal.generated.h"

UCLASS()
class BLOCKGAME_API ABlockBoxHeal : public ABlockBoxMagma
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockBoxHeal();
};

inline ABlockBoxHeal::ABlockBoxHeal()
{
	Event = &ABlockGameCharacter::HealByBox;
}

