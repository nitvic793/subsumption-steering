// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Utility Functions
 */
class SUBSUMPTIONSTEERING_API Utility
{
public:
	Utility();
	~Utility();

	static FVector Truncate(FVector vector, float max)
	{
		float length;
		FVector f;
		vector.ToDirectionAndLength(f, length);
		float i = max / length;
		i = (i < 1.f) ? i : 1.0;
		vector = vector * i;
		return vector;
	}
	
	static const float Length(const FVector& v)
	{
		float l;
		FVector f;
		v.ToDirectionAndLength(f, l);
		return l;
	}
	
	static void SetAngle(FVector& v, float angle)
	{
		float l = Length(v);
		v.X = FMath::Cos(angle) * l;
		v.Y = FMath::Sin(angle) * l;
	}
};
