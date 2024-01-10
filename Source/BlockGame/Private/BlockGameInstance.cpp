// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGameInstance.h"

uint32 GetValueTypeHash(const FBlockData& Src)
{
	return FCrc::MemCrc32(&Src, sizeof(Src));
}

uint32 GetTypeHash(const FBlockData& other)
{
	return FCrc::MemCrc32(&other, sizeof(other));
}

void UBlockGameInstance::AddBox(FBlockData blockData)
{
	savedBlocks.Add(blockData);
}

void UBlockGameInstance::DeleteBox(FBlockData blockData)
{
	// savedBlocks.RemoveByHash(GetValueTypeHash(blockData), GetValueTypeHash(blockData));
	savedBlocks.Remove(blockData);
}
