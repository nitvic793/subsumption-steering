// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorInterface.h"

BehaviorInterface::BehaviorInterface()
{
	velocity = FVector(5, 0, 0);
	target = FVector(600, 600, 80);
}

BehaviorInterface::BehaviorInterface(AActor* actr) 
	: actor(actr)
{
	velocity = FVector(5, 0, 0);
	target = FVector(600, 600, 80);
}

BehaviorInterface::~BehaviorInterface()
{
}

void BehaviorInterface::Start(std::function<void(BehaviorInterface*)> callback) 
{
	callback(this);
}

void BehaviorInterface::RunBehavior() 
{

}
