// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structs/FBlockData.h"
#include "BlockSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API UBlockSaveGame : public USaveGame
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TSet<FBlockData> SavedBlocks;

public:
	[[nodiscard]] TSet<FBlockData> GetSavedBlocks() const
	{
		return SavedBlocks;
	}

	void SetSavedBlocks(const TSet<FBlockData>& NewSavedBlocks)
	{
		this->SavedBlocks = NewSavedBlocks;
	}
};
