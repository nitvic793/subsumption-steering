// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorInterface.h"

BehaviorInterface::BehaviorInterface()
{
}

BehaviorInterface::BehaviorInterface(AActor* actr) 
	: actor(actr)
{
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
