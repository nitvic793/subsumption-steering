// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"
#include <vector>
#include <string>

struct NodePriority
{
	BehaviorInterface* behavior;
	int priority;

	NodePriority(BehaviorInterface* InBehavior)
	{
		behavior = InBehavior;
		priority = behavior->GetPriority();
	}

	NodePriority()
	{
		behavior = NULL;
		priority = 0;
	}
};

struct NodePriorityPredicate
{
	bool operator() (const NodePriority& A, const NodePriority& B) const
	{
		return A.priority > B.priority;
	}
};

enum BehaviorEnum {
	WANDER,
	STEER
};

/**
 * Behavior Arbiter
 */
class SUBSUMPTIONSTEERING_API BehaviorArbiter
{
protected:
	AActor *actor;
	TMap<BehaviorEnum, BehaviorInterface*> behaviorMap;
	TArray<NodePriority> behaviorQueue;
	BehaviorInterface* currentBehavior;
public:
	BehaviorArbiter(AActor *);
	~BehaviorArbiter();
	void AddBehaviorLevel(BehaviorEnum, BehaviorInterface*);
	void StartBehavior();
	void RunBehavior();
	void UpdateBehavior();
};