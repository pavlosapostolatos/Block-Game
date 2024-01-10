// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs\FBlockData.h"
#include "BlockGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API UBlockGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TSet<FBlockData> savedBlocks;

public:

	UBlockGameInstance() = default;

	[[nodiscard]] TSet<FBlockData> SavedBlocks() const
	{
		return savedBlocks;
	}

	UFUNCTION(BlueprintCallable)
	void AddBox(FBlockData blockData);

	UFUNCTION(BlueprintCallable)
	void DeleteBox(FBlockData blockData);

	// void SetSavedBlocks(const TSet<BlockData>& SavedBlocks)
	// {
	// 	savedBlocks = SavedBlocks;
	// }
};
