// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveMap.h"

#include "BlockGameInstance.h"
#include "BlockSaveGame.h"
#include "Kismet/GameplayStatics.h"

void ASaveMap::BeginPlay()
{
	UBlockGameInstance* gi = Cast<UBlockGameInstance>(UGameplayStatics::GetGameInstance(this));
	FString LevelName =  UGameplayStatics::GetCurrentLevelName(this);

	UBlockSaveGame* save = Cast<UBlockSaveGame>(UGameplayStatics::LoadGameFromSlot(LevelName,0));

	if(save == nullptr)
		return;
	
	check(gi);

	for (FBlockData block : save->GetSavedBlocks())
	{
		gi->AddBox(block);
		GetWorld()->SpawnActor<ABlockBox>(block.type, UE::Math::TTransform(block.rotation, block.location));
	}

}
