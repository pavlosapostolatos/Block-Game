// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\BlockBox.h"

// Sets default values
ABlockBox::ABlockBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockBox::DestroyBox()
{
	Destroy();
}

