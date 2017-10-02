// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"
/**
 * 
 */
class SUBSUMPTIONSTEERING_API FleeBehavior : public BehaviorInterface
{
public:
	FleeBehavior(AActor*);
	~FleeBehavior();
	void Start(std::function<void(BehaviorInterface*)>);
	void RunBehavior();
};
