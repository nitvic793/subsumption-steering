// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorInterface.h"
/**
 * 
 */
class SUBSUMPTIONSTEERING_API EatBehavior : public BehaviorInterface
{
public:
	EatBehavior(AActor*);
	~EatBehavior();
	void Start(std::function<void(BehaviorInterface*)>);
	void RunBehavior();
};
