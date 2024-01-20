// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "HeartWidget.generated.h"
/**
 * 
 */
UCLASS()
class BLOCKGAME_API UHeartWidget : public UUserWidget
{
public:

	UFUNCTION(Blueprintable)
	void SetHealth(int Health);
	
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UImage>> Hearts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance, meta = (AllowPrivateAccess = "true"))
	FSlateBrush FullHeart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance, meta = (AllowPrivateAccess = "true"))
	FSlateBrush HalfHeart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance, meta = (AllowPrivateAccess = "true"))
	FSlateBrush EmptyHeart;
};
