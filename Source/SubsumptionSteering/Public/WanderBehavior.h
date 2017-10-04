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
	void Start(std::function<void(BehaviorInterface*)>);
	void RunBehavior(float deltaTime);
protected:
	FVector target;
	float maxVelocity = 10.f;
	FVector desiredVelocity;
	float mass = 10.f;
	float maxForce = 10.f;
	float maxSpeed = 3.f;
	float wanderAngle = 0.f;
	float slowingRadius = 300.f;
	FVector velocity;
	FVector position;
};
