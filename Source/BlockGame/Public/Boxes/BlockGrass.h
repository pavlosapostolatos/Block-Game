// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockBox.h"
#include "BlockGrass.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API ABlockGrass : public ABlockBox
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
};
