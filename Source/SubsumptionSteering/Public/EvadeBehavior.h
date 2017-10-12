// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"

/**
 * Technically not evade. Repurposed to keep actors within bounds
 */
class SUBSUMPTIONSTEERING_API EvadeBehavior : public BehaviorInterface
{
public:
	EvadeBehavior(AActor*);
	~EvadeBehavior();
	void Start(std::function<void(BehaviorInterface*)>);
	void RunBehavior(float deltaTime);
private:
	AActor* floor;
};
