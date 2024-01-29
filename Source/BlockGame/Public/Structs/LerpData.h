#pragma once

// #include "LerpData.generated.h"
DECLARE_DELEGATE(FLerpFinishFunction);

struct LerpData
{
	float LerpAmount = 0.0f;
	float LerpDuration = 3.0f; // Duration in seconds
	float LerpTimer = 0.0f;
	float StartValue = 0.0f;
	float EndValue = 1.0f;
	float bLerping = false;
	int8 direction : 2 = 1;
	FLerpFinishFunction FinishFunction;
};