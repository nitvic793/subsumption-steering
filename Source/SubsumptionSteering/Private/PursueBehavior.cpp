// Fill out your copyright notice in the Description page of Project Settings.

#include "PursueBehavior.h"

PursueBehavior::PursueBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
}

PursueBehavior::~PursueBehavior()
{
}

void PursueBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	callback(this);
}

void PursueBehavior::RunBehavior()
{

}