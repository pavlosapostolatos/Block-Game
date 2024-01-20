// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HeartWidget.h"

#include "Macros.h"

void UHeartWidget::SetHealth(int Health)
{
	const int32 SafeMaxPlayerHealth = MAX_PLAYER_HEALTH - MAX_PLAYER_HEALTH % Hearts.Num();
	Health = std::min(Health, SafeMaxPlayerHealth);
	const int FullHeartStep = SafeMaxPlayerHealth / Hearts.Num();

	int FullHearts = Health / FullHeartStep + (Health % FullHeartStep > 0.5f * FullHeartStep);
	bool isHalfHeart = Health % FullHeartStep && Health % FullHeartStep < 0.5f * FullHeartStep;

	int i;
	for (i = 0; i < FullHearts; ++i)
	{
		Hearts[i]->SetBrush(FullHeart);
	}

	if(isHalfHeart)
		Hearts[i]->SetBrush(HalfHeart);

	for (++i; i < Hearts.Num(); ++i)
	{
		Hearts[i]->SetBrush(EmptyHeart);
	}

}
