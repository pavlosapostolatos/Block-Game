// Fill out your copyright notice in the Description page of Project Settings.


#include "Stairs.h"

AStairs::AStairs()
{

}


UE::Math::TQuat<double> AStairs::GetRotation(FVector originLocation,FVector SpawnLocation)
{
	FVector rotation = originLocation - SpawnLocation;
	return rotation.Rotation().GridSnap(FRotator(90, 90, 0)).Quaternion();
}