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
	FVector target;
	float maxVelocity = 20.f;
	FVector desiredVelocity;
	float mass = 10.f;
	float maxForce = 20.f;
	float maxSpeed = 3.f;
	float wanderAngle = 0.f;
	float slowingRadius = 300.f;
	FVector velocity;
	FVector position;

	BehaviorInterface();
	BehaviorInterface(AActor *);
	virtual ~BehaviorInterface();
	virtual void Start(std::function<void(BehaviorInterface*)>);
	virtual void RunBehavior(float deltaTime);
	virtual void SyncInfo();
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
