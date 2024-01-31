// Fill out your copyright notice in the Description page of Project Settings.


#include "Boxes/BlockGrass.h"

void ABlockGrass::BeginPlay()
{
	Super::BeginPlay();
	// UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BlockMaterial, nullptr);
	// //
	// DynMaterial->SetScalarParameterValue("Size", 3.0);
	// DynMaterial->SetScalarParameterValue("DestroyAmount", 0.0);
	//

	// int i=-1;
	// for (UMaterialInterface* MI : SM_Block->GetMaterials())
	// {
	// 	i++;
	// 	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MI, nullptr);
	// 	SM_Block->SetMaterial(i, DynMaterial);
	// }
}