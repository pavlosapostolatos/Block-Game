// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGameInstance.h"

#include "BlockSaveGame.h"
#include "Kismet/GameplayStatics.h"

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

void UBlockGameInstance::SaveGame()
{
	SaveGame(UGameplayStatics::GetCurrentLevelName(this));
}
void UBlockGameInstance::SaveGame(FString LevelName)
{
	UBlockSaveGame* save;
	if(! UGameplayStatics::DoesSaveGameExist(LevelName,0))
	{
		save = Cast<UBlockSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UBlockSaveGame::StaticClass()));
	}
	else
	{
		save = Cast<UBlockSaveGame>(UGameplayStatics::LoadGameFromSlot(LevelName,0));
	}

	save->SetSavedBlocks(this->SavedBlocks());
	UGameplayStatics::SaveGameToSlot(save,LevelName, 0);
}

void UBlockGameInstance::AutoSave()
{
	SaveGame(UGameplayStatics::GetCurrentLevelName(this) + "AutoSave");
}
