// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAME_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	int health;

public:
	[[nodiscard]] int Health() const
	{
		return health;
	}

	void SetHealth(int Health)
	{
		health = Health;
	}
};
