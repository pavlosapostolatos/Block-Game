// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHealthWidget.generated.h"

UCLASS()
class BLOCKGAME_API UMyHealthWidget : public UUserWidget
{
public:


private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	int health;

public:
	// UMyHealthWidget() = default;
	
	[[nodiscard]] int Health() const
	{
		return health;
	}

	void SetHealth(int Health)
	{
		health = Health;
	}
};
