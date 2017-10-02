// Fill out your copyright notice in the Description page of Project Settings.

#include "EatBehavior.h"

EatBehavior::EatBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
}

EatBehavior::~EatBehavior()
{
}

void EatBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	callback(this);
}

void EatBehavior::RunBehavior()
{

}