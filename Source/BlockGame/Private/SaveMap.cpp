// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveMap.h"

#include "BlockGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ASaveMap::BeginPlay()
{
	UBlockGameInstance* gi = Cast<UBlockGameInstance>(UGameplayStatics::GetGameInstance(this));

	check(gi);

	for (FBlockData block : gi->SavedBlocks())
	{
		GetWorld()->SpawnActor<ABlockBox>(block.type, UE::Math::TTransform(block.rotation, block.location));
	}

}
