// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SaveMap.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API ASaveMap : public ALevelScriptActor //Assign at open level blueprint
{
	GENERATED_BODY()

	// TList<BlockData>* SaveData;cant use struct in Tlist

	// UPROPERTY()
	// TList<ABlockBox*> SaveData;
	// UPROPERTY()
	// TSet<ABlockBox*> SaveData2;
	
	// TSet<ABlockBox*> SaveData;

protected:
	virtual void BeginPlay() override;
};
