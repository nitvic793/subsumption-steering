// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"

/**
 * 
 */
class SUBSUMPTIONSTEERING_API AttackBehavior : public BehaviorInterface
{
public:
	AttackBehavior(AActor*);
	~AttackBehavior();
	void Start(std::function<void(BehaviorInterface*)>);
	void RunBehavior(float deltaTime);
protected:
	float currentTime = 0.f;
	AActor* targetAnimal;
};
