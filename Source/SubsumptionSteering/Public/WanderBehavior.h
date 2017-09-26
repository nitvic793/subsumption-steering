// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"

/**
 * 
 */
class SUBSUMPTIONSTEERING_API WanderBehavior : public BehaviorInterface
{
public:
	WanderBehavior(AActor*);
	~WanderBehavior();
};
