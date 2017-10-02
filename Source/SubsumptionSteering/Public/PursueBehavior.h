// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"
/**
 * 
 */
class SUBSUMPTIONSTEERING_API PursueBehavior : public BehaviorInterface
{
public:
	PursueBehavior(AActor*);
	~PursueBehavior();
	void Start(std::function<void(BehaviorInterface*)>);
	void RunBehavior();
};
