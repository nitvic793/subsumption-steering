// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <functional>

/**
 * 
 */
class SUBSUMPTIONSTEERING_API BehaviorInterface
{
protected:
	AActor *actor;
	int priority = 1;
public:
	BehaviorInterface();
	BehaviorInterface(AActor *);
	virtual ~BehaviorInterface();
	virtual void Start(std::function<void()>);
	virtual void RunBehavior();
	void SetActor(AActor *actr)
	{
		this->actor = actr;
	}

	void SetPriority(int priority)
	{
		this->priority = priority;
	}

	int GetPriority()
	{
		return priority;
	}
};
