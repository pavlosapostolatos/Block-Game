#pragma once

#include "CoreMinimal.h"
#include "ABlockBoxMagma.h"
#include "ABlockBoxHeal.generated.h"

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
	event = &ABlockGameCharacter::Heal;
}

