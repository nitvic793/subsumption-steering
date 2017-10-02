// Fill out your copyright notice in the Description page of Project Settings.

#include "EvadeBehavior.h"

EvadeBehavior::EvadeBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
}

EvadeBehavior::~EvadeBehavior()
{
}

void EvadeBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	callback(this);
}

void EvadeBehavior::RunBehavior()
{

}